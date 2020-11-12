/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
  This software was developed at the National Institute of Standards and
  Technology by employees of the Federal Government in the course of
  their official duties. Pursuant to titleElement 17 Section 105 of the United
  States Code this software is not subject to copyright protection and
  is in the public domain.
  NIST assumes no responsibility whatsoever for its use by other parties,
  and makes no guarantees, expressed or implied, about its quality,
  reliability, or any other characteristic.

  We would appreciate acknowledgement if the software is used.

  NIST ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION AND
  DISCLAIM ANY LIABILITY OF ANY KIND FOR ANY DAMAGES WHATSOEVER RESULTING
  FROM THE USE OF THIS SOFTWARE.

 * Modified by: Fabian Eckermann <fabian.eckermann@udo.edu> (CNI)
 *              Moritz Kahlert <moritz.kahlert@udo.edu> (CNI)
 */

#include "ns3/lte-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/lte-v2x-helper.h"
#include "ns3/config-store.h"
#include "ns3/lte-hex-grid-enb-topology-helper.h"
#include <ns3/buildings-helper.h>
#include <ns3/cni-urbanmicrocell-propagation-loss-model.h>
#include <ns3/constant-position-mobility-model.h>
#include <ns3/spectrum-analyzer-helper.h>
#include <ns3/multi-model-spectrum-channel.h>
#include "ns3/ns2-mobility-helper.h"
#include <cfloat>
#include <sstream>
#include <iostream>
#include <string>
using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("v2x_communication_mode_4");

std::string simtime = "log_simtime_v2x.csv";
std::string rx_data = "log_rx_data_v2x.csv";
std::string tx_data = "log_tx_data_v2x.csv";
//std::string connections = "log_connections_v2x.csv";
std::string positions = "log_positions_v2x.csv";

//Ptr<OutputStreamWrapper> log_connections;
Ptr<OutputStreamWrapper> log_simtime;
Ptr<OutputStreamWrapper> log_positions;
Ptr<OutputStreamWrapper> log_rx_data;
Ptr<OutputStreamWrapper> log_tx_data;

uint32_t ctr_totRx = 0; 	
uint32_t rx0 = 0; 
uint32_t rx1 = 0; 
uint32_t rx2 = 0; 
uint32_t rx3 = 0;
uint32_t rx4 = 0;
uint32_t rx5 = 0; //RSU收包
uint32_t ctr_totTx = 0; 	
uint32_t tx0 = 0;
uint32_t tx1 = 0;
uint32_t tx2 = 0;
uint32_t tx3 = 0;
uint32_t tx4 = 0;
uint32_t tx5 = 0; //RSU发包
uint16_t lenCam;
double baseline= 150.0; 
double baseline_rsu= 300.0; //RSU通信范围为300m    
Vector Obs_pos(100,0,1.5);//障碍物位置
uint16_t platoon_avoid = 11; //车辆排状态，11：初始未判断状态；10：绕道行驶；01：停车
uint16_t order_avoid = 0;//0：初始状态；1：头车运动模型改变；2.3.4.5同理
uint16_t mob_change[5] = {0,0,0,0,0};//车辆是否改变运动模型指标，0：未改变；1：已改变

NodeContainer ueAllNodes; //车辆节点+RSU节点
NodeContainer ueVehNodes; //车辆节点

void
configSet (Ptr<LteHelper> lteHelper)
{
    lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::NakagamiPropagationLossModel"));
}

void
PrintStatus (uint32_t s_period, Ptr<OutputStreamWrapper> log_simtime)
{
    *log_simtime->GetStream() << Simulator::Now ().GetSeconds () << ";" << ctr_totRx << ";" << ctr_totTx << ";" << (double) ctr_totRx / ctr_totTx << std::endl;
    std::cout << "t=" <<  Simulator::Now().GetSeconds() << "\t Rx/Tx="<< ctr_totRx << "/" << (ctr_totTx) << "\t PRR=" << (double) ctr_totRx / (ctr_totTx) <<std::endl;
    Simulator::Schedule(Seconds(s_period), &PrintStatus, s_period,log_simtime);
}

void
SidelinkV2xAnnouncementMacTrace(Ptr<Socket> socket)  //发送包（广播）
{
    Ptr <Node> node = socket->GetNode();
    int Txid = node->GetId();   //发包id
    uint32_t simTime = Simulator::Now().GetMilliSeconds();
    Ptr<MobilityModel> posMobility = node->GetObject<MobilityModel>();
    Vector posTx = posMobility->GetPosition();
    for (uint8_t i=0; i<ueAllNodes.GetN();i++)
    {
        Ptr<MobilityModel> mob = ueAllNodes.Get(i)->GetObject<MobilityModel>();
        Vector posRx = mob->GetPosition();
        double distance = sqrt(pow(((int)posTx.x - (int)posRx.x),2.0)+pow(((int)posTx.y - (int)posRx.y),2.0));
        if  (distance > 0 && distance <= baseline)  //距离大于0且小于基线距离
        {
			tx0++;
            ctr_totTx++;
        }
    }
    switch (platoon_avoid)//根据车辆排状态更改运动模型
    {
        case 11: break;//初始未判断状态
		case 10: //绕道行驶
		if( order_avoid == Txid || mob_change[Txid] == 1)
		{
			if ( (int)posTx.y < 9 )
			{
				  Ptr<ConstantVelocityMobilityModel> constantVelocity = node->GetObject<ConstantVelocityMobilityModel> ();
				  constantVelocity->SetVelocity(Vector (6, 8, 0));//m/s  
			}
			else 
			{
				  Ptr<ConstantVelocityMobilityModel> constantVelocity = node->GetObject<ConstantVelocityMobilityModel> ();
				  constantVelocity->SetVelocity(Vector (10, 0, 0));//m/s  
			}		
			if( order_avoid == Txid )
			{
				  order_avoid++;	
			}
			mob_change[Txid] = 1;
		}break;
		case 01://停车
		if( order_avoid == Txid || mob_change[Txid] == 1)
		{				
			Ptr<ConstantVelocityMobilityModel> constantVelocity = node->GetObject<ConstantVelocityMobilityModel> ();
			constantVelocity->SetVelocity(Vector (0, 0, 0));//m/s 		
			if( order_avoid == Txid )
			{
				 order_avoid++;	
			}	
			mob_change[Txid] = 1;
		}break;
    }
    // Generate CAM
    std::ostringstream msgCam;
    msgCam << Txid << ";" << simTime << ";" << (int) posTx.x << ";" << (int) posTx.y << ";" << 0 << ";" << 0 << '\0';
    Ptr<Packet> packet = Create<Packet>((uint8_t*)msgCam.str().c_str(),lenCam);
    socket->Send(packet);

    *log_tx_data->GetStream() << tx0 << ";" << tx1 << ";"<< tx2 << ";"<< tx3 << ";" << tx4 << ";" << ctr_totTx << ";" << simTime << ";"  << Txid << ";" << (int) posTx.x << ";" << (int) posTx.y << std::endl;
}

void
SidelinkV2xMulticastMacTrace(Ptr<Socket> socket)  //发送包（组播）
{
    Ptr <Node> node = socket->GetNode();
    int Txid = node->GetId();   //发包id
    uint32_t simTime = Simulator::Now().GetMilliSeconds();
    Ptr<MobilityModel> posMobility = node->GetObject<MobilityModel>();
    Vector posTx = posMobility->GetPosition();
    for (uint8_t i=0; i<ueVehNodes.GetN();i++)
    {
        int Rxid = ueVehNodes.Get(i)->GetId();
        uint16_t id = abs(Rxid-Txid);
	    Ptr<MobilityModel> mob = ueVehNodes.Get(i)->GetObject<MobilityModel>();
        Vector posRx = mob->GetPosition();
	    double distance = sqrt(pow(((int)posTx.x - (int)posRx.x),2.0)+pow(((int)posTx.y - (int)posRx.y),2.0));
        if  (distance > 0 && distance <= baseline && (Rxid == 0 || id == 1))  //头车或前后车
        {
            switch (Txid)
            {
                case 1: tx1++; break;
                case 2: tx2++; break;
                case 3: tx3++; break;
                case 4: tx4++; break;
                default: break;
            }
            ctr_totTx++;
        }
    }
    switch (platoon_avoid)//根据车辆排状态更改运动模型
    {
	case 11: break;//初始未判断状态
	case 10: //绕道行驶
	if( order_avoid == Txid || mob_change[Txid] == 1)
        {
		if ( (int)posTx.y < 9 )
		{
			Ptr<ConstantVelocityMobilityModel> constantVelocity = node->GetObject<ConstantVelocityMobilityModel> ();
			constantVelocity->SetVelocity(Vector (6, 8, 0));//m/s  
		}
		else 
		{
			Ptr<ConstantVelocityMobilityModel> constantVelocity = node->GetObject<ConstantVelocityMobilityModel> ();
			constantVelocity->SetVelocity(Vector (10, 0, 0));//m/s  
		}		
		if( order_avoid == Txid )
		{
			order_avoid++;	
		}
		mob_change[Txid] = 1;
	}break;
	case 01://停车
	if( order_avoid == Txid || mob_change[Txid] == 1)
	{				
		Ptr<ConstantVelocityMobilityModel> constantVelocity = node->GetObject<ConstantVelocityMobilityModel> ();
		constantVelocity->SetVelocity(Vector (0, 0, 0));//m/s 		
		if( order_avoid == Txid )
		{
			order_avoid++;	
		}	
		mob_change[Txid] = 1;
	}break;
    }
    // Generate CAM
    std::ostringstream msgCam;
    msgCam << Txid << ";" << simTime << ";" << (int) posTx.x << ";" << (int) posTx.y << ";" << 0 << ";" << 0 << '\0';
    Ptr<Packet> packet = Create<Packet>((uint8_t*)msgCam.str().c_str(),lenCam);
    socket->Send(packet);

    *log_tx_data->GetStream() << tx0 << ";" << tx1 << ";"<< tx2 << ";"<< tx3 << ";" << tx4 << ";" << ctr_totTx << ";" << simTime << ";"  << Txid << ";" << (int) posTx.x << ";" << (int) posTx.y << std::endl;
}

void
SidelinkV2xUnicastMacTrace(Ptr<Socket> socket)  //发送包（RSU单播）
{
    Ptr <Node> node = socket->GetNode();
    int Txid = node->GetId();   //发包id
    uint32_t simTime = Simulator::Now().GetMilliSeconds();
    Ptr<MobilityModel> posMobility = node->GetObject<MobilityModel>();
    Vector posTx = posMobility->GetPosition();
    Ptr<MobilityModel> mob = ueAllNodes.Get(0)->GetObject<MobilityModel>();
    Vector posRx = mob->GetPosition();
    double distance = sqrt(pow(((int)posTx.x - (int)posRx.x),2.0)+pow(((int)posTx.y - (int)posRx.y),2.0));
    if  (distance > 0 && distance <= baseline_rsu)  
    {
	    tx5++;
        ctr_totTx++;
    }
    // Generate CAM
    std::ostringstream msgCam;
    msgCam << Txid << ";" << simTime << ";" << (int) posTx.x << ";" << (int) posTx.y << ";" << (int) (Obs_pos.x) << ";" << (int) Obs_pos.y << '\0';
    Ptr<Packet> packet = Create<Packet>((uint8_t*)msgCam.str().c_str(),lenCam);
    socket->Send(packet);

    *log_tx_data->GetStream() << tx0 << ";" << tx1 << ";"<< tx2 << ";"<< tx3 << ";" << tx4 << ";" << ctr_totTx << ";" << simTime << ";"  << Txid << ";" << (int) posTx.x << ";" << (int) posTx.y << std::endl;
}

static void
ReceivePacket(Ptr<Socket> socket)  //接收包
{
    Ptr<Node> node = socket->GetNode();
    Ptr<MobilityModel> posMobility = node->GetObject<MobilityModel>();  //获取节点的移动模型
    Vector posRx = posMobility->GetPosition();    //获取接收者的位置
    uint32_t RxsimTime = Simulator::Now().GetMilliSeconds();
    int Rxid = node->GetId();
    Ptr<Packet> packet = socket->Recv ();
    uint8_t *buffer = new uint8_t[packet->GetSize()];
    packet->CopyData(buffer,packet->GetSize());
    std::string s = std::string((char*)buffer);  //接收包字符串
    size_t pos = 0;
    std::string copy = s;
    std::string token;
    int Txid;   
    int TxsimTime;
    int posTx_x;
    int posTx_y;
    int Obs_pos_x;
    int Obs_pos_y;
    for (int i = 0; i < 5; i++)
    {
        if (copy.find(";") != std::string::npos) //查找字符串copy是否包含子串";"，如果没找到，返回一个特别的标志，c++中用npos表示
        {
            pos = copy.find(";");
            token = copy.substr(0,pos);  //获取；前的子串
            switch (i)
            {
                case 0:  Txid = atoi(token.c_str());             break;
                case 1:  TxsimTime = atoi(token.c_str());        break;
                case 2:  posTx_x = atoi(token.c_str());          break;
                case 3:  posTx_y = atoi(token.c_str());          break;
                case 4:  Obs_pos_x = atoi(token.c_str());        break;
                default: break;
            }
            copy.erase (0,pos+1);
        }
    }
    Obs_pos_y = atoi(copy.c_str());  //atoi 函数是把字符串的数字转为数字型的数值
    
    double distance = sqrt(pow((posTx_x - (int)posRx.x),2.0)+pow((posTx_y - (int)posRx.y),2.0));
    if ( Txid == 5 && Rxid == 0 && distance <= baseline_rsu && platoon_avoid == 11 )
    {
        double distance_obs = sqrt(pow((Obs_pos_x - (int)posRx.x),2.0)+pow((Obs_pos_y - (int)posRx.y),2.0));
        if ( distance_obs <= 20.0 )
	    {
	        platoon_avoid=01; //和障碍物距离小于20m，停车（暂定20m）
	    }
	    else 
	    {
	        platoon_avoid=10;//和障碍物距离大于20m，绕道行驶
	    }
    }

    if ( (Txid != 5) && (distance <= baseline))        //距离小于基线距离
    {
        switch (Rxid)
        {
             case 0: rx0++; break;
             case 1: rx1++; break;
             case 2: rx2++; break;
             case 3: rx3++; break;
             case 4: rx4++; break;
             case 5: rx5++; break;
             default: break;
        }
        ctr_totRx++;
    }
    else if ( (Txid == 5) && (distance <= baseline_rsu) ) 
    {
         rx0++;
         ctr_totRx++;
    }
	*log_rx_data->GetStream() << rx0 << ";" << rx1 << ";" << rx2 << ";" << rx3 << ";" << rx4 << ";" <<ctr_totRx<< ";"<< RxsimTime << ";" << Rxid << ";"  << Txid << ";"  << TxsimTime << ";" << posTx_x << ";" << posTx_y << ";" << (int)posRx.x << ";"  <<  (int)posRx.y << ";" << distance << ";" << platoon_avoid << std::endl;
   
}

int
main (int argc, char *argv[])
{
    LogComponentEnable ("v2x_communication_mode_4", LOG_INFO);

    // Initialize some values
    // NOTE: commandline parser is currently (05.04.2019) not working for uint8_t (Bug 2916)

    uint16_t simTime = 20;                 // Simulation time in seconds 仿真时间
    uint32_t numVeh = 5;                  // Number of vehicles      车辆数量
    lenCam = 190;                           // Length of CAM message in bytes [50-300 Bytes]  CAM消息的长度
    double ueTxPower = 22;                // Transmission power in dBm    传输功率
    double probResourceKeep = 0.8;          // Probability to select the previous resource again [0.0-0.8]  再次选择先前的资源的概率
    uint32_t mcs = 20;                      // Modulation and Coding Scheme  编码调制方式
    bool harqEnabled = false;               // Retransmission enabled     重传
    bool adjacencyPscchPssch = true;        // Subchannelization scheme   子信道方案
    bool partialSensing = false;            // Partial sensing enabled (actual only partialSensing is false supported)  支持部分感知(只支持部分感知)
    uint16_t sizeSubchannel = 10;           // Number of RBs per subchannel    每个子信道的RB数量
    uint16_t numSubchannel = 3;             // Number of subchannels per subframe  每个子帧的子通道数
    uint16_t startRbSubchannel = 0;         // Index of first RB corresponding to subchannelization  子信道化的对应的第一个RB下标
    uint16_t pRsvp = 100;		    // Resource reservation interval  资源预定时间间隔ms
    uint16_t t1 = 4;                        // T1 value of selection window  选择窗口的T1值0-4
    uint16_t t2 =100;                      // T2 value of selection window  选择窗口的T2值20-100
    uint16_t slBandwidth;                   // Sidelink bandwidth            链路带宽
    std::string tracefile;                  // Name of the tracefile         跟踪文件的名称

    // Command line arguments 命令行参数
    CommandLine cmd;
    cmd.AddValue ("time", "Simulation Time", simTime);
    cmd.AddValue ("numVeh", "Number of Vehicles", numVeh);
    cmd.AddValue ("adjacencyPscchPssch", "Scheme for subchannelization", adjacencyPscchPssch);
    cmd.AddValue ("sizeSubchannel", "Number of RBs per Subchannel", sizeSubchannel);
    cmd.AddValue ("numSubchannel", "Number of Subchannels", numSubchannel);
    cmd.AddValue ("startRbSubchannel", "Index of first subchannel index", startRbSubchannel);
    cmd.AddValue ("T1", "T1 Value of Selection Window", t1);
    cmd.AddValue ("T2", "T2 Value of Selection Window", t2);
    cmd.AddValue ("lenCam", "Packetsize in Bytes", lenCam);
    cmd.AddValue ("mcs", "Modulation and Coding Scheme", mcs);
    cmd.AddValue ("pRsvp", "Resource Reservation Interval", pRsvp);
    cmd.AddValue ("probResourceKeep", "Probability for selecting previous resource again", probResourceKeep);
    cmd.AddValue ("log_simtime", "name of the simtime logfile", simtime);
    cmd.AddValue ("log_rx_data", "name of the rx data logfile", rx_data);
    cmd.AddValue ("log_tx_data", "name of the tx data logfile", tx_data);
    cmd.AddValue ("tracefile", "Path of ns-3 tracefile", tracefile);      //ns3跟踪文件路径
    cmd.AddValue ("baseline", "Distance in which messages are transmitted and must be received", baseline);  //发送和必须接收消息的距离
    cmd.Parse (argc, argv);

    AsciiTraceHelper ascii; //创建文件流转码
    log_simtime = ascii.CreateFileStream(simtime);
    log_rx_data = ascii.CreateFileStream(rx_data);
    log_tx_data = ascii.CreateFileStream(tx_data);
    //log_connections = ascii.CreateFileStream(connections);
    log_positions = ascii.CreateFileStream(positions);

    NS_LOG_INFO ("Starting network configuration...");

    // Set the UEs power in dBm
    Config::SetDefault ("ns3::LteUePhy::TxPower", DoubleValue (ueTxPower));
    Config::SetDefault ("ns3::LteUePhy::RsrpUeMeasThreshold", DoubleValue (-69)); //-10

    // Enable V2X communication on PHY layer
    Config::SetDefault ("ns3::LteUePhy::EnableV2x", BooleanValue (true));

    // Set power
    Config::SetDefault ("ns3::LteUePowerControl::Pcmax", DoubleValue (ueTxPower));
    Config::SetDefault ("ns3::LteUePowerControl::PsschTxPower", DoubleValue (ueTxPower));
    Config::SetDefault ("ns3::LteUePowerControl::PscchTxPower", DoubleValue (ueTxPower));

    if (adjacencyPscchPssch)
    {
        slBandwidth = sizeSubchannel * numSubchannel;
    }
    else
    {
        slBandwidth = (sizeSubchannel+2) * numSubchannel;
    }

    // Configure for UE selected
    Config::SetDefault ("ns3::LteUeMac::UlBandwidth", UintegerValue(slBandwidth)); //带宽30MHz
    Config::SetDefault ("ns3::LteUeMac::EnableV2xHarq", BooleanValue(harqEnabled)); //重传,false
    Config::SetDefault ("ns3::LteUeMac::EnableAdjacencyPscchPssch", BooleanValue(adjacencyPscchPssch)); //true,启用相邻的PSCCH + PSSCH方案
    Config::SetDefault ("ns3::LteUeMac::EnablePartialSensing", BooleanValue(partialSensing)); //false
    Config::SetDefault ("ns3::LteUeMac::SlGrantMcs", UintegerValue(mcs)); //20
    Config::SetDefault ("ns3::LteUeMac::SlSubchannelSize", UintegerValue (sizeSubchannel)); //10
    Config::SetDefault ("ns3::LteUeMac::SlSubchannelNum", UintegerValue (numSubchannel)); //3
    Config::SetDefault ("ns3::LteUeMac::SlStartRbSubchannel", UintegerValue (startRbSubchannel)); //0
    Config::SetDefault ("ns3::LteUeMac::SlPrsvp", UintegerValue(pRsvp)); //100ms
    Config::SetDefault ("ns3::LteUeMac::SlProbResourceKeep", DoubleValue(probResourceKeep)); //0.8
    Config::SetDefault ("ns3::LteUeMac::SelectionWindowT1", UintegerValue(t1)); //4
    Config::SetDefault ("ns3::LteUeMac::SelectionWindowT2", UintegerValue(t2)); //100

    //Config::SetDefault ("ns3::LteEnbRrc::DefaultTransmissionMode", UintegerValue (1));
    //UintegerValue uintegerValue;
    ConfigStore inputConfig;
    inputConfig.ConfigureDefaults();

    NodeContainer ueLeaderNodes; //头车
    NodeContainer ueFollowNodes; //跟随车
    NodeContainer RsuNodes;//RSU

    NS_LOG_INFO ("Installing Mobility Model...");

    if (tracefile.empty())
    {
	//创建numVeh个用户车辆
	ueLeaderNodes.Create (1);  //头车
	ueFollowNodes.Create (numVeh-1);  //跟随车
	RsuNodes.Create (1); //RSU
	//所有节点放进ueAllNodes节点容器
	ueAllNodes.Add (ueLeaderNodes);
	ueAllNodes.Add (ueFollowNodes);
	ueAllNodes.Add (RsuNodes);
	//车辆节点放进ueVehNodes节点容器
	ueVehNodes.Add (ueLeaderNodes);
	ueVehNodes.Add (ueFollowNodes);

	MobilityHelper mobVeh;  //固定速度移动模型
	mobVeh.SetMobilityModel ("ns3::ConstantVelocityMobilityModel");

	Ptr<ListPositionAllocator> staticVeh[ueVehNodes.GetN()];
	uint16_t k= ueVehNodes.GetN()-1;
	for (uint16_t i=0; i<ueVehNodes.GetN();i++)
	{   
		uint16_t x = (k-i)*10;
		staticVeh[i] = CreateObject<ListPositionAllocator>();
		staticVeh[i]->Add (Vector (x,0,1.5));
		mobVeh.SetPositionAllocator (staticVeh[i]);
		mobVeh.Install (ueVehNodes.Get(i));
	}

	Ptr<ListPositionAllocator> constantVelocity[ueVehNodes.GetN()];  //所有车具有相同的随机速度
	for (uint16_t i=0; i<ueVehNodes.GetN();i++)
	{
		Ptr<ConstantVelocityMobilityModel> constantVelocity = ueVehNodes.Get(i)->GetObject<ConstantVelocityMobilityModel> ();
		Ptr<UniformRandomVariable> rand = CreateObject<UniformRandomVariable> ();
		constantVelocity->SetVelocity(Vector (10, 0, 0));
	}
		
	//RSU位置设置
	MobilityHelper mobRsu;  //节点静止移动模型
	mobRsu.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	Ptr<ListPositionAllocator> staticRsu[RsuNodes.GetN()];
	staticRsu[0] = CreateObject<ListPositionAllocator>();
	staticRsu[0]->Add (Vector (370,0,7));
	mobRsu.SetPositionAllocator (staticRsu[0]); 
	mobRsu.Install (RsuNodes);
		
    }
    else
    {
        // Create nodes
        ueLeaderNodes.Create (1);
        ueFollowNodes.Create (numVeh-1);
        RsuNodes.Create (1);
        ueAllNodes.Add (ueLeaderNodes);
        ueAllNodes.Add (ueFollowNodes);
        ueAllNodes.Add (RsuNodes);
        ueVehNodes.Add (ueLeaderNodes);
        ueVehNodes.Add (ueFollowNodes);

        Ns2MobilityHelper ns2 = Ns2MobilityHelper(tracefile);
        ns2.Install();
    }


    NS_LOG_INFO ("Creating helpers...");
    // EPC
    Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
    Ptr<Node> pgw = epcHelper->GetPgwNode();

    // LTE Helper
    Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
    lteHelper->SetEpcHelper(epcHelper);
    lteHelper->DisableNewEnbPhy(); // Disable eNBs for out-of-coverage modelling

    // V2X
    Ptr<LteV2xHelper> lteV2xHelper = CreateObject<LteV2xHelper> ();
    lteV2xHelper->SetLteHelper (lteHelper);

    // Configure eNBs' antenna parameters before deploying them.
    lteHelper->SetEnbAntennaModelType ("ns3::NistParabolic3dAntennaModel"); //抛物线3D天线模型

    // Set pathloss model
    // FIXME: InstallEnbDevice overrides PathlossModel Frequency with values from Earfcn

    lteHelper->SetAttribute ("UseSameUlDlPropagationCondition", BooleanValue(true));  //使用相同的UlDl传播条件
    Config::SetDefault ("ns3::LteEnbNetDevice::UlEarfcn", StringValue ("54990"));
    lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::CniUrbanmicrocellPropagationLossModel"));  //城市微蜂窝传播路径损耗  高速公路场景下可能要改一下？


    // Create eNB Container
    NodeContainer eNodeB;
    eNodeB.Create(1);

    // Topology eNodeB
    Ptr<ListPositionAllocator> pos_eNB = CreateObject<ListPositionAllocator>();
    pos_eNB->Add(Vector(5,-10,30));    //基站的矢量位置

    //  Install mobility eNodeB
    MobilityHelper mob_eNB;
    mob_eNB.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mob_eNB.SetPositionAllocator(pos_eNB);
    mob_eNB.Install(eNodeB);

    // Install Service
    NetDeviceContainer enbDevs = lteHelper->InstallEnbDevice(eNodeB);

    // Required to use NIST 3GPP model
    BuildingsHelper::Install (eNodeB);
    BuildingsHelper::Install (ueAllNodes);
    BuildingsHelper::MakeMobilityModelConsistent ();

    // Install LTE devices to all UEs 
    NS_LOG_INFO ("Installing UE's network devices...");
    lteHelper->SetAttribute("UseSidelink", BooleanValue (true));
    NetDeviceContainer ueFollowDevs = lteHelper->InstallUeDevice (ueFollowNodes);
    NetDeviceContainer ueLeaderDevs = lteHelper->InstallUeDevice (ueLeaderNodes);
    NetDeviceContainer ueRsuDevs = lteHelper->InstallUeDevice (RsuNodes);
    NetDeviceContainer ueDevs; //车辆节点放进ueDevs节点容器
    ueDevs.Add (ueLeaderDevs);
    ueDevs.Add (ueFollowDevs);
    NetDeviceContainer ueRxDevs; //跟随车节点和RSU放进ueRxDevs节点容器
    ueRxDevs.Add (ueFollowDevs);
    ueRxDevs.Add (ueRsuDevs);

    // Install the IP stack on the UEs
    NS_LOG_INFO ("Installing IP stack...");
    InternetStackHelper internet;
    internet.Install (ueAllNodes);

    // Assign IP adress to UEs
    NS_LOG_INFO ("Allocating IP addresses and setting up network route...");

    Ipv4AddressHelper address;

    address.SetBase ("10.1.1.0","255.255.255.0");
    Ipv4InterfaceContainer LeaderInterfaces;
    LeaderInterfaces = address.Assign (ueLeaderDevs);

    address.SetBase ("10.1.2.0","255.255.255.0");
    Ipv4InterfaceContainer FollowInterfaces;
    FollowInterfaces = address.Assign (ueFollowDevs);

    address.SetBase ("10.1.3.0","255.255.255.0");
    Ipv4InterfaceContainer RsuInterfaces;
    RsuInterfaces = address.Assign (ueRsuDevs);
	
    Ipv4StaticRoutingHelper Ipv4RoutingHelper;

    for(uint32_t u = 0; u < ueAllNodes.GetN(); ++u)
    {
        Ptr<Node> ueNode = ueAllNodes.Get(u);    //Get
        // Set the default gateway for the UE 为UE设置默认网关
        Ptr<Ipv4StaticRouting> ueStaticRouting = Ipv4RoutingHelper.GetStaticRouting(ueNode->GetObject<Ipv4>());
        ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress(), 1);
    }

    NS_LOG_INFO("Attaching UE's to LTE network...");
    //Attach each UE to the best available eNB 
    lteHelper->Attach(ueLeaderDevs);
    lteHelper->Attach(ueFollowDevs);
	lteHelper->Attach(ueRsuDevs);

    NS_LOG_INFO ("Creating Multicast sidelink groups...");
    std::vector<NetDeviceContainer> txGroups;
    txGroups = lteV2xHelper->AssociateForV2xMulticast(ueDevs, numVeh); 
    lteV2xHelper->PrintGroups(txGroups);

    NS_LOG_INFO ("Installing applications...");
	
    std::vector<uint32_t> groupL2Addresses;
    uint32_t groupL2Address = 0x00;
    uint16_t application_port = 8000; // Application port to TX/RX 端口号
	
    //设置头车广播
    Ipv4Address BroadcastAddress ="226.0.0.0";
	
    Ptr<LteSlTft> tft = Create<LteSlTft> (LteSlTft::TRANSMIT, BroadcastAddress, groupL2Address);
    lteV2xHelper->ActivateSidelinkBearer (Seconds(0.0), ueLeaderDevs, tft);
    tft = Create<LteSlTft> (LteSlTft::RECEIVE, BroadcastAddress, groupL2Address);
    lteV2xHelper->ActivateSidelinkBearer (Seconds(0.0),ueRxDevs, tft);

    //客户端
    Ptr<Socket> client = Socket::CreateSocket(ueLeaderDevs.Get(0)->GetNode(),TypeId::LookupByName ("ns3::UdpSocketFactory"));
    client->Bind();
    client->Connect(InetSocketAddress(BroadcastAddress,application_port));
    client->SetAllowBroadcast(true);
    client->ShutdownRecv();
	
    //服务端
    for (uint16_t m=0; m<ueRxDevs.GetN(); m++)
    {
	Ptr<Socket> server = Socket::CreateSocket(ueRxDevs.Get(m)->GetNode(),TypeId::LookupByName ("ns3::UdpSocketFactory"));
	server->Bind(InetSocketAddress (Ipv4Address::GetAny (), application_port));
	server->SetRecvCallback (MakeCallback (&ReceivePacket));
    }

    Ptr<LteUeMac> leaderueMac = DynamicCast<LteUeMac>(ueLeaderDevs.Get (0)->GetObject<LteUeNetDevice> ()->GetMac () );
    leaderueMac->TraceConnectWithoutContext ("SidelinkV2xAnnouncement", MakeBoundCallback (&SidelinkV2xAnnouncementMacTrace, client)); 

    groupL2Addresses.push_back (groupL2Address);
    groupL2Address++;

    //跟随车组播
    Ipv4AddressGenerator::Init(Ipv4Address ("225.0.0.0"), Ipv4Mask("255.0.0.0"));//组播地址
    Ipv4Address MulticastAddress = Ipv4AddressGenerator::NextAddress (Ipv4Mask ("255.0.0.0"));

    std::vector<NetDeviceContainer>::iterator gIt;
    for(gIt=txGroups.begin(); gIt != txGroups.end(); gIt++)
    {
            NetDeviceContainer txUe ((*gIt).Get(0));
            NetDeviceContainer rxUes = lteV2xHelper->RemoveNetDevice ((*gIt), txUe.Get (0));

            Ptr<LteSlTft> tft1 = Create<LteSlTft> (LteSlTft::TRANSMIT, MulticastAddress, groupL2Address);
            lteV2xHelper->ActivateSidelinkBearer (Seconds(0.0), txUe, tft1);
            tft1 = Create<LteSlTft> (LteSlTft::RECEIVE, MulticastAddress, groupL2Address);
            lteV2xHelper->ActivateSidelinkBearer (Seconds(0.0), rxUes, tft1);

            //客户端
            Ptr<Socket> host = Socket::CreateSocket(txUe.Get(0)->GetNode(),TypeId::LookupByName ("ns3::UdpSocketFactory"));
            host->Bind();
            host->Connect(InetSocketAddress(MulticastAddress,application_port));
            //host->SetAllowBroadcast(true);
            host->ShutdownRecv();

            Ptr<LteUeMac> ueMac = DynamicCast<LteUeMac>( txUe.Get (0)->GetObject<LteUeNetDevice> ()->GetMac () );
            ueMac->TraceConnectWithoutContext ("SidelinkV2xAnnouncement", MakeBoundCallback (&SidelinkV2xMulticastMacTrace, host));

            //服务端
            for (uint16_t j=0; j<rxUes.GetN(); j++)
            {
				Ptr<Socket> server = Socket::CreateSocket(rxUes.Get(j)->GetNode(),TypeId::LookupByName ("ns3::UdpSocketFactory"));
				server->Bind(InetSocketAddress (Ipv4Address::GetAny (), application_port));
				server->SetRecvCallback (MakeCallback (&ReceivePacket));
            }

            //store and increment addresses 存储地址和增量地址
            groupL2Addresses.push_back (groupL2Address);
            groupL2Address++;
            MulticastAddress = Ipv4AddressGenerator::NextAddress (Ipv4Mask ("255.0.0.0"));
     }
	 
    //RSU单播
    Ipv4Address LeaderAddress = LeaderInterfaces.GetAddress(0);//头车地址
    Ptr<LteSlTft> tft2 = Create<LteSlTft> (LteSlTft::TRANSMIT, LeaderAddress, groupL2Address);
    lteV2xHelper->ActivateSidelinkBearer (Seconds(0.0), ueRsuDevs.Get(0), tft2);
    tft2 = Create<LteSlTft> (LteSlTft::RECEIVE,LeaderAddress, groupL2Address);
    lteV2xHelper->ActivateSidelinkBearer (Seconds(0.0), ueLeaderDevs.Get(0), tft2);
    //客户端
    Ptr<Socket> rsu0 = Socket::CreateSocket(ueRsuDevs.Get(0)->GetNode(),TypeId::LookupByName ("ns3::UdpSocketFactory"));
    rsu0->Bind();
    //服务端
    Ptr<Socket> Leader = Socket::CreateSocket(ueLeaderDevs.Get(0)->GetNode(),TypeId::LookupByName ("ns3::UdpSocketFactory"));
    Leader->Bind(InetSocketAddress (Ipv4Address::GetAny(), application_port));
    Leader->SetRecvCallback (MakeCallback (&ReceivePacket));//收包函数
    //发起连接
    rsu0->Connect(InetSocketAddress(LeaderAddress,application_port));
    Ptr<LteUeMac> rsu0ueMac = DynamicCast<LteUeMac>(ueRsuDevs.Get(0)->GetObject<LteUeNetDevice> ()->GetMac () );
    rsu0ueMac->TraceConnectWithoutContext ("SidelinkV2xAnnouncement", MakeBoundCallback (&SidelinkV2xUnicastMacTrace,rsu0));  //发包函数
	
    groupL2Addresses.push_back (groupL2Address);
    groupL2Address++;

 
        NS_LOG_INFO ("Creating Sidelink Configuration...");
        Ptr<LteUeRrcSl> ueSidelinkConfiguration = CreateObject<LteUeRrcSl>();
        ueSidelinkConfiguration->SetSlEnabled(true);
        ueSidelinkConfiguration->SetV2xEnabled(true);

        LteRrcSap::SlV2xPreconfiguration preconfiguration;
        preconfiguration.v2xPreconfigFreqList.freq[0].v2xCommPreconfigGeneral.carrierFreq = 54890;
        preconfiguration.v2xPreconfigFreqList.freq[0].v2xCommPreconfigGeneral.slBandwidth = slBandwidth;

        preconfiguration.v2xPreconfigFreqList.freq[0].v2xCommTxPoolList.nbPools = 1;
        preconfiguration.v2xPreconfigFreqList.freq[0].v2xCommRxPoolList.nbPools = 1;

        SlV2xPreconfigPoolFactory pFactory;
        pFactory.SetHaveUeSelectedResourceConfig (true);
        pFactory.SetSlSubframe (std::bitset<20> (0xFFFFF));
        pFactory.SetAdjacencyPscchPssch (adjacencyPscchPssch);
        pFactory.SetSizeSubchannel (sizeSubchannel);
        pFactory.SetNumSubchannel (numSubchannel);
        pFactory.SetStartRbSubchannel (startRbSubchannel);
        pFactory.SetStartRbPscchPool (0);
        pFactory.SetDataTxP0 (-4);
        pFactory.SetDataTxAlpha (0.9);

        preconfiguration.v2xPreconfigFreqList.freq[0].v2xCommTxPoolList.pools[0] = pFactory.CreatePool ();
        preconfiguration.v2xPreconfigFreqList.freq[0].v2xCommRxPoolList.pools[0] = pFactory.CreatePool ();  

        ueSidelinkConfiguration->SetSlV2xPreconfiguration (preconfiguration);

        // Print Configuration
        *log_rx_data->GetStream() << "RxPackets0;RxPackets1;RxPackets2;RxPackets3;RxPackets4;RxPackets;RxTime;RxId;TxId;TxTime;TxxPos;TxyPos;RxxPos;RxyPos;distance" << std::endl;
        *log_tx_data->GetStream() << "Tx0Packets;Tx1Packets;Tx2Packets;Tx3Packets;Tx4Packets;TxPackets;TxTime;TxId;TxxPos;TxyPos" << std::endl;

        NS_LOG_INFO ("Installing Sidelink Configuration..."); 
        lteHelper->InstallSidelinkV2xConfiguration (ueLeaderDevs, ueSidelinkConfiguration);
        lteHelper->InstallSidelinkV2xConfiguration (ueFollowDevs, ueSidelinkConfiguration);
	lteHelper->InstallSidelinkV2xConfiguration (ueRsuDevs, ueSidelinkConfiguration);

        NS_LOG_INFO ("Enabling LTE traces...");
        lteHelper->EnableTraces();

        *log_simtime->GetStream() << "Simtime;TotalRx;TotalTx;PRR" << std::endl;
        Simulator::Schedule(Seconds(1), &PrintStatus, 1, log_simtime);

        NS_LOG_INFO ("Reconfig the PathLossModel...");
        Simulator::Schedule(Seconds(10), &configSet, lteHelper);

        NS_LOG_INFO ("Starting Simulation...");
        Simulator::Stop(MilliSeconds(simTime*1000+40));
        Simulator::Run();
        Simulator::Destroy();

        NS_LOG_INFO("Simulation done.");
        return 0;
}
