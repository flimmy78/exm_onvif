#ifndef DEVINFO_H
#define DEVINFO_H
#define DEV_GUID_BYTE 8
#include <iniparser.h>
#include <devres.h>
#include <devinfo_virdev.h>

#define MAX_AUDIO_ENCODER			4			//最大支持的音频编码器数
#define	MAX_VIDEO_ENCODER		5			//最大支持的视频编码器数
#define MAX_AUDIO_DECODER       4           //最大支持音频解码器数量
#define MAX_FRAME_SIZE         200*1024

///GT硬件产品系列定义
#define GTDEV_FAMILY_GTVS       0       ///GTVS系列视频服务器
#define GTDEV_FAMILY_GTVM       1       ///GTVM系列虚拟服务器


/********************设备信息结构定义************************************************************/
#if 0
typedef struct{			//视频服务器的子设备信息结构
	int 		type;		//子设备类型
	int 		no;			//子设备在同类设备中的序号
	char 	*name;		//子设备名
	char 	*node;		//子设备节点
	char 	*driver;		//子设备驱动程序
}DevType_T;
#endif

//GT1000系列视频服务器型号定义
#define		T_GT1000				0		//老版本的视频服务器统称GT1000
#define 	T_GT1000_STR			"GT1000_Q2"
#define 	T_GTVS1024_O			1		//视频2个编码器4路视频输入，带画面分割器
#define 	T_GTVS1024_O_STR		"GTVS1024-O"
#define 	T_GTVS1024_OA			2		//比GT1024-O多了音频放大器
#define 	T_GTVS1024_OA_STR		"GTVS1024-OA"
#define		T_GTVS1011				3
#define		T_GTVS1011_STR			"GTVS1011"
#define		T_GTVS1011_A			4
#define		T_GTVS1011_A_STR		"GTVS1011-A"
#define 	T_GTVS1011_O			5		//1个视频编码器带画面分割器
#define 	T_GTVS1011_O_STR		"GTVS1011-O"		
#define 	T_GTVS1011_OA			6		//比GT1011-O多了音频放大器
#define 	T_GTVS1011_OA_STR		"GTVS1011-OA"
#define 	T_GTVS1011_N			7		//一个视频编码器，不带画面分割器，带2个网口
#define 	T_GTVS1011_N_STR		"GTVS1011-N+"
#define 	T_GTVS1011_AN			8		//比GT1011-N+多了音频放大器
#define 	T_GTVS1011_AN_STR		"GTVS1011-AN+"
#define		T_GTVS1014_O			9
#define		T_GTVS1014_O_STR		"GTVS1014-O"
#define		T_GTVS1014_OA			10
#define		T_GTVS1014_OA_STR		"GTVS1014-OA"
#define		T_GTVS1021			11
#define 	T_GTVS1021_STR			"GTVS1021"
#define		T_GT1001			12
#define		T_GT1001_STR			"GT1001"	//2个端子输入2个端子输出带视频环出


#define 	T_GTVM3001			100
#define		T_GTVM3001_STR			"GTVM3001"

#define		T_GTVM3111			111
#define		T_GTVM3111_STR			"GTVM3111"


#define		T_GTVS3021			20		
#define		T_GTVS3021_STR	"GTVS3021"
#define		T_GTVS3022			21
#define		T_GTVS3022_STR "GTVS3022"
#define		T_GTVS3024			22		
#define		T_GTVS3024_STR	"GTVS3024"
#define		T_GTVS3021L			23
#define		T_GTVS3021L_STR "GTVS3021L"
#define		T_GTVS3024L			24
#define		T_GTVS3024L_STR "GTVS3024L"	
//#define		T_GTVS3121			25
//#define		T_GTVS3121_STR  "GTVS3121"
#define		T_GTMV3121			25		//// lsk 2010-3-18
#define		T_GTMV3121_STR  "GTMV3121"

#define		T_GTVS3124			26
#define		T_GTVS3124_STR  "GTVS3124"

#define		T_GTMV3122			27		//// zw 2010-08-12  --modify 2010-11-22
#define		T_GTMV3122_STR	"GTMV3122"

#define     T_GTIP1004         28      //lc 2012-11-15
#define     T_GTIP1004_STR  "GTIP1004"

#define     T_GTIP2004         29      //lc 2014-10-15
#define     T_GTIP2004_STR  "GTIP2004"




#define		T_GTVDxxxx			200










#define 	T_GT_UNKNOW			(-1)		//未知类型
#define 	T_GT_UNKNOW_STR			"UNKNOW TYPE"
#if 0
typedef struct{//GT系列DVSR描述定义
	int	type;		//#设备型号
	char *comment;	//对于该型号的说明
	int	trignum;	//#设备最高报警输入数
	int	outnum;		//输出端子数
	int	com;	  	//#设备串口数不需要在界面上设置
	int	quad;		//#是否有画面分割器，1表示有 0表示没有
	int	osd;		//是否有osd,1表示有,0表示没有
	int	videonum;	//#系统最多视频输入数(和移动侦测有关),在quad=0时videonum应该为1	
	int	videoencnum;	//#视频编码器数量
	int	hqencnum;	//录像的通道数
	int	ide;		//#1表示有cf卡或硬盘 0表示没有
	int	eth_port;	//#网口数 1表示一个 2表示两个
	int	list_num;	//子设备列表中的有效子设备数
	DevType_T **list;	//子设备列表
}GTSeriesDVSR;
#endif
//子设备类型定义
#define SUB_DEV_QUAD	0	//画面分割器
#define SUB_DEV_VENC	1	//视频编码器
#define SUB_DEV_IDE	2	//硬盘
#define SUB_DEV_ACDC	3	//音频芯片	
#define SUB_DEV_COM	4	//串口
#define SUB_DEV_NETPORT 5	//网口
/******************************************************************************************************/

/**********************************************************************************************
 * 函数名       :get_devinfo_version
 * 功能 :       获取devinfo库的版本信息
 * 输入 :无
 * 返回值       :秒数devinfo库版本信息的字符串指针
  **********************************************************************************************/
const char *get_devinfo_version(void);


/**********************************************************************************************
 * 函数名	:init_devinfo()
 * 功能	:初始化设备信息(应用程序刚启动的时候调用)
 * 输入	:无
 * 返回值	:0表示正常，负值表示出错
 * 注		:应用程序在刚启动的时候需要调用这个函数从/conf/devinfo.ini中读取系统信息
 *			如果/conf/devinfo.ini不存在，则把设备信息设置成初始值，并返回-1
  **********************************************************************************************/
int init_devinfo(void);

/**********************************************************************************************
 * 函数名	:get_devid()
 * 功能	:应用程序调用获得设备的dev_id(应该已经调用过了init_devinfo())
 * 输入	:无
 * 输出 	:buf:应用程序需要存放devid的缓冲区地址,返回时填充buf的长度必须足够长大于DEV_GUID_BYTE
 * 返回值	:正值表示填充到buf中的有效字节数，负值表示出错
  **********************************************************************************************/
int get_devid(unsigned char *buf);
/**********************************************************************************************
 * 函数名	:get_devid_str()
 * 功能	:应用程序调用获得设备的guid的字符串
 * 输入	:无
 * 返回值	:指向描述guid信息的字符串指针
  **********************************************************************************************/
char* get_devid_str(void);
/**********************************************************************************************
 * 函数名       :get_lfc_flag()
 * 功能 :应用程序调用获得设备出厂标志
 * 输入 :无
 * 返回值       :1=出厂，0=在家 ，-1出错
 **********************************************************************************************/
int get_lfc_flag(void);

/**********************************************************************************************
 * 函数名	:set_devid_str()
 * 功能	:应用程序调用设置设备的guid值,字符串格式
 * 输入	:id_str:字符串表示的设备guid值
 * 输出 	:
 * 返回值	:0表示成功 负值表示出错 -EINVAL表示输入参数格式不对
  **********************************************************************************************/
int set_devid_str(char *id_str);

/**********************************************************************************************
 * 函数名	:set_devid()
 * 功能	:应用程序调用设置设备的guid值,二进制格式
 * 输入	:buf:二进制描述的guid值，长度为DEV_GUID_BYTE字节
 * 输出 	:
 * 返回值	:0表示成功 负值表示出错 -EINVAL表示输入参数格式不对
  **********************************************************************************************/
int set_devid(unsigned char *buf);

/**********************************************************************************************
 * 函数名	:get_hd_capacity()
 * 功能	:获取设备的磁盘容量信息(以MB为单位)
 * 输入	:无
 * 返回值	:正值表示设备的磁盘容量，负值表示出错
 **********************************************************************************************/
int get_hd_capacity(void);

/**********************************************************************************************
 * 函数名	:set_hd_capacity()
 * 功能	:设置设备的磁盘容量值
 * 输入	:value:程序检测到的磁盘容量值MB为单位
 * 返回值	:0表示成功，负值表示出错
 **********************************************************************************************/
int set_hd_capacity(int value);

/**********************************************************************************************
 * 函数名	:get_hd_type()
 * 功能	:获取磁盘类型
 * 输入	:无
 * 返回值	:0-CF,1-HD,-1-none
 **********************************************************************************************/
int get_hd_type(void);


/**********************************************************************************************
 * 函数名	:get_hd_nodename()
 * 功能	:获取磁盘节点名称
 * 输入	:diskno, 磁盘编号，0，1，2。。
 * 返回值	:节点名称，NULL表示失败
 **********************************************************************************************/
char * get_hd_nodename(int diskno);

/**********************************************************************************************
 * 函数名	:get_disk_no()
 * 功能	:获取磁盘数目
 * 返回值	:磁盘数目
 **********************************************************************************************/
int get_disk_no(void);


/**********************************************************************************************
 * 函数名	:set_devtype_str()
 * 功能	:设置设备的型号字符串
 * 输入	:type_str:描述设备型号的字符串
 * 返回值	:0表示成功，负值表示失败,-EINVAL表示参数是不支持的类型
 **********************************************************************************************/
int set_devtype_str(char *type);

/**********************************************************************************************
 * 函数名	:get_devtypestr()
 * 功能	:应用程序调用获得描述设备类型的字符串
 * 输入	:无
 * 返回值	:描述设备类型字符串的指针
 **********************************************************************************************/
char * get_devtype_str(void);

/**********************************************************************************************
 * 函数名	:get_devtype()
 * 功能	:应用程序调用获得设备类型代码
 * 输入	:无
 * 返回值	:设备类型代码
 **********************************************************************************************/
int 	get_devtype(void);

/**********************************************************************************************
 * 函数名	:get_lvfac_time()
 * 功能	:获取设备的出厂时间
 * 输入	:无
 * 返回值	:设备出厂时间的结构指针
 **********************************************************************************************/
struct tm * get_lvfac_time(void);
/**********************************************************************************************
 * 函数名	:get_lvfac_time()
 * 功能	:获取设备的出厂时间
 * 输入	:无
 * 返回值	:0表示正确 负值表示出错  -EINVAL表示 参数错误
 **********************************************************************************************/
int  set_lvfac_time(struct tm *lv);
/**********************************************************************************************
 * 函数名	:get_batch_seq()
 * 功能	:获取生产批次字符串
 * 输入	:无
 * 返回值	:指向生产批次字符串的指针
 **********************************************************************************************/
char *get_batch_seq(void);

/**********************************************************************************************
 * 函数名	:get_board_seq()
 * 功能	:获取板卡批次字符串
 * 输入	:无
 * 返回值	:指向板卡批次字符串的指针
 **********************************************************************************************/
char *get_board_seq(void);

/**********************************************************************************************
 * 函数名	:set_batch_seq()
 * 功能	:设置生产批次字符串
 * 输入	:生产批次信息
 * 返回值	:0表示成功负值表示失败
 **********************************************************************************************/
int set_batch_seq(char *seq);

/**********************************************************************************************
 * 函数名	:set_board_seq()
 * 功能	:设置板卡批次字符串
 * 输入	:板卡批次信息
 * 返回值	:0表示成功负值表示失败
 **********************************************************************************************/
int set_board_seq(char *seq);


/**********************************************************************************************
 * 函数名	:get_total_com()
 * 功能	:获取设备的总串口数
 * 输入	:无
 * 返回值	:正值表示设备的总串口数,负值表示出错
 **********************************************************************************************/
int get_total_com(void);


/**********************************************************************************************
 * 函数名	:get_video_num()
 * 功能	:获取设备可接入的视频总数
 * 输入	:无
 * 返回值	:可接入的视频数
 **********************************************************************************************/
int get_video_num(void);
/**********************************************************************************************
 * 函数名	:get_videoenc_num()
 * 功能	:获取视频编码器数
 * 输入	:无
 * 返回值	:视频编码器数
 **********************************************************************************************/
int get_videoenc_num(void);
/**********************************************************************************************
 * 函数名	:get_ide_flag()
 * 功能	:获取设备是否有存储设备标志
 * 输入	:无
 * 返回值	:1表示有硬盘 或CF卡 2表示有SD卡 0表示没有
 * **********************************************************************************************/
int	get_ide_flag(void);
/**********************************************************************************************
 * 函数名	:get_cpu_iic_flag()
 * 功能	:获取是否使用cpu的iic总线控制视频ad转换芯片
 * 输入	:无
 * 返回值	:1表示使用0表示不使用
 **********************************************************************************************/
int get_cpu_iic_flag(void);

/**********************************************************************************************
 * 函数名	:get_trigin_num()
 * 功能	:获取输入端子数
 * 输入	:无
 * 返回值	:设备上的输入端子总数
 **********************************************************************************************/
int	get_trigin_num(void);
/**********************************************************************************************
 * 函数名	:get_alarmout_num()
 * 功能	:获取输出端子数
 * 输入	:无
 * 返回值	:设备上的输出端子数
 **********************************************************************************************/
int get_alarmout_num(void);
/**********************************************************************************************
 * 函数名	:get_eth_num()
 * 功能	:获取网口数
 * 输入	:无
 * 返回值	:设备上的网口数
 **********************************************************************************************/
int get_eth_num(void);

/**********************************************************************************************
 * 函数名	:get_quad_flag()
 * 功能	:获取画面分割器是否有效标志
 * 输入	:无
 * 返回值	:1表示有画面分割器 0表示没有
 **********************************************************************************************/
int get_quad_flag(void);
/**********************************************************************************************
 * 函数名	:get_osd_flag()
 * 功能	:获取是否有osd标志
 * 输入	:无
 * 返回值	:1表示有0表示没有
 **********************************************************************************************/
int get_osd_flag(void);

/**********************************************************************************************
 * 函数名	:get_audio_num()
 * 功能	:获取音频通道个数
 * 输入	:无
 * 返回 :音频通道个数
 **********************************************************************************************/
int get_audio_num(void);

/***********************************************************************************************
 * 函数名:get_prog_ver
 * 功能  :获取设备软件版本号字符串
 * 输入  :无
 * 返回  :描述设备软件版本号的字符串指针
 **********************************************************************************************/
char *get_prog_ver(void);

/***********************************************************************************************
 * 函数名:get_dev_family
 * 功能  :获取设备属于哪个系列的产品
 * 输入  :无
 * 返回  :产品系列代码 GTDEV_FAMILY_GTVS GTDEV_FAMILY_GTVM
 **********************************************************************************************/
int get_dev_family(void);

/***********************************************************************************************
 * 函数名:get_videoname_by_index
 * 功能  :获取设备视频通道名称
 * 输入  :index 视频通道号
 * 返回  :描述设备视频通道名称的字符串指针
 **********************************************************************************************/
unsigned char *get_videoname_by_index(int channel);


//打印支持的设备型号信息
void print_support_deivce_list(void);

#endif




