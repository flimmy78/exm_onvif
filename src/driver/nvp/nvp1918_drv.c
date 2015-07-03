#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>

#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/system.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/list.h>
#include <asm/delay.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/poll.h>
#include <asm/bitops.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <linux/moduleparam.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>

#include "gpio_i2c.h"
#include "nvp1918.h"
#include "video.h"
#include "coax_protocol.h"
#include "motion.h"
#include "audio.h"
//extern void sil9034_1080i60_init(void);
//extern void sil9034_1080i50_init(void);
//extern void sil9034_1080p30_init(void);

unsigned int vdec_mode = VDEC_PAL_960;
unsigned int vdec_cnt = 0;

unsigned int vdec_slave_addr[2] = {0x60, 0x62};

module_param(vdec_mode, uint, S_IRUGO);

int check_id(unsigned int dec)
{
	int ret;
	gpio_i2c_write(dec, 0xFF, 0x01);
	ret = (gpio_i2c_read(dec, 0xf4)<<8) | (gpio_i2c_read(dec, 0xf5));
	return ret;
}

int vdec_open(struct inode * inode, struct file * file)
{
	return 0;
} 

int vdec_close(struct inode * inode, struct file * file)
{
	return 0;
}

//int vdec_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
int vdec_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	unsigned int on;
	unsigned long ptz_ch;
	unsigned int value;
	unsigned int sens[16];
	vdec_video_mode vmode;
	vdec_video_adjust v_adj;
	vdec_video_loss video_loss;//yk add 20130408
	switch (cmd)
	{
        case IOC_VDEC_SET_VIDEO_MODE:
            if (copy_from_user(&vmode, arg, sizeof(vdec_video_mode)))
				return -1;

			vdec_mode = vmode.mode;

			if(vmode.mode == VDEC_NTSC)
			{
				nvp1918_720h_nt();
			}
			else if(vmode.mode == VDEC_PAL)
			{	
				nvp1918_720h_pal();
			}
			else if(vmode.mode == VDEC_NTSC_960)
			{	
				nvp1918_960h_nt();
			}
			else 
			{	
				nvp1918_960h_pal();
			}
			break;

		case IOC_VDEC_SET_BRIGHTNESS:
            if(copy_from_user(&v_adj, arg, sizeof(vdec_video_adjust))) return -1;
			vdec_video_set_brightness(v_adj.ch, v_adj.value, vdec_mode&1);
			break;
		case IOC_VDEC_SET_CONTRAST:
			if(copy_from_user(&v_adj, arg, sizeof(vdec_video_adjust))) return -1;
			vdec_video_set_contrast(v_adj.ch, v_adj.value, vdec_mode&1);
			break;
		case IOC_VDEC_SET_HUE:
			if(copy_from_user(&v_adj, arg, sizeof(vdec_video_adjust))) return -1;
			vdec_video_set_hue(v_adj.ch, v_adj.value, vdec_mode&1);
			break;
		case IOC_VDEC_SET_SATURATION:
			if(copy_from_user(&v_adj, arg, sizeof(vdec_video_adjust))) return -1;
			vdec_video_set_saturation(v_adj.ch, v_adj.value, vdec_mode&1);
			break;
		case IOC_VDEC_SET_SHARPNESS:
			break;

		case IOC_VDEC_PTZ_PELCO_INIT:
			vdec_coaxial_init();
			pelco_coax_mode();
			break;
		case IOC_VDEC_PTZ_PELCO_RESET:
			pelco_reset();
			break;
		case IOC_VDEC_PTZ_PELCO_SET:
			pelco_set();
			break;
		case IOC_VDEC_PTZ_CHANNEL_SEL:
            if (copy_from_user(&ptz_ch, arg, sizeof(ptz_ch)))
			{
				return -1;
			}
			vdec_coaxial_select_ch(ptz_ch);
			break;
		case IOC_VDEC_PTZ_PELCO_UP:
		 	pelco_up();
		 	break;
		case IOC_VDEC_PTZ_PELCO_DOWN:
		 	pelco_down();
		 	break;
		case IOC_VDEC_PTZ_PELCO_LEFT:
		 	pelco_left();
		 	break;
		case IOC_VDEC_PTZ_PELCO_RIGHT:
			pelco_right();
			break;
		case IOC_VDEC_PTZ_PELCO_FOCUS_NEAR:
			//FIXME
			pelco_osd();
			//pelco_focus_near();
		 	break;
		case IOC_VDEC_PTZ_PELCO_FOCUS_FAR:
			//FIXME
			pelco_set();
			//pelco_focus_far();
		 	break;
		case IOC_VDEC_PTZ_PELCO_ZOOM_WIDE:
			//pelco_zoom_wide();
			pelco_iris_open();
		 	break;
		case IOC_VDEC_PTZ_PELCO_ZOOM_TELE:
			//pelco_zoom_tele();
			pelco_iris_close();
			break;

		case IOC_VDEC_INIT_MOTION:
			vdec_motion_init();
			hi3520_init_blank_data(0);
			break;
		case IOC_VDEC_ENABLE_MOTION:
			break;
		case IOC_VDEC_DISABLE_MOTION:
			break;
		case IOC_VDEC_SET_MOTION_AREA:
			break;
		case IOC_VDEC_GET_MOTION_INFO:
			vdec_get_motion_info(0);
			break;
		case IOC_VDEC_SET_MOTION_DISPLAY:
            if(copy_from_user(&on, arg, sizeof(unsigned int))) return -1;
			vdec_motion_display(0,on);
			break;
		case IOC_VDEC_SET_MOTION_SENS:
            if(copy_from_user(&sens, arg, sizeof(unsigned int)*16)) return -1;
			vdec_motion_sensitivity(sens);
			break;
		case IOC_VDEC_ENABLE_LOW_RES:
			vdec_low_resoultion_enable(0xff);
			break;
		case IOC_VDEC_DISABLE_LOW_RES:
			vdec_low_resoultion_disable(0xff);
			break;
		case IOC_VDEC_ENABLE_BW:
			vdec_bw_detection_enable(0xff);
			break;
		case IOC_VDEC_DISABLE_BW:
			vdec_bw_detection_disable(0xff);
			break;
		case IOC_VDEC_READ_BALCK_COUNT:
			value = vdec_bw_black_count_read(0);
			copy_to_user(arg,&value, sizeof(int));
			break;
		case IOC_VDEC_READ_WHITE_COUNT:
			break;
		case IOC_VDEC_4CH_VIDEO_SEQUENCE:
			break;
//yk add 20130409
		case IOC_VIDEO_GET_VIDEO_LOSS:
		{
			//printk("this is video loss\n");
			if (copy_from_user(&video_loss, arg, sizeof(vdec_video_loss)))
				return -1;
			//printk("this is video loss1\n");
			if(video_loss.chip!=0){printk("the board have only one chip 0\n");return -1;}
			if(video_loss.ch>=4){printk("the chip only have 4 channel\n");return -1;}
			unsigned int value=0;
			unsigned short reg_val=0x01;
			unsigned int tmp;
			value |= (0x60)<<24;//i2c地址
			value |= (0xff)<<16;//nvp寄存器地址
			value |= reg_val;//nvp寄存器要写的值
			/*此片nvp在i2c的0x60地址上*/
			gpio_i2c_write(0x60, 0xff, 0x01);//选择nvp的寄存器，bank组1， 0x60是i2c的地址，0xff是nvp寄存器的地址，0x01是向寄存器写值
			tmp=gpio_i2c_read(0x60, 0xd8);//读nvp的bank1组的0xd8地址，可得到视频丢失情况
			if((tmp >> video_loss.ch)&0x01 )
				video_loss.is_lost=1;
			else
				video_loss.is_lost=0;
			if (copy_to_user(arg, &video_loss, sizeof(video_loss)))
                		return -1;
			//printk("this is video loss2\n");
			break;
		}
//yk add 20130412
		case IOC_VIDEO_GET_IMAGE_ADJUST:
		{
			nvp_image_adjust ad;
			if (copy_from_user(&ad, arg, sizeof(nvp_image_adjust)))
				return -1;
			if(ad.chip!=0){printk("the board have only one chip 0\n");return -1;}
			if(ad.ch>=4){printk("the chip only have 4 channel\n");return -1;}
			gpio_i2c_write(0x60, 0xff, 0x00);//选择nvp的寄存器，bank组0， 0x60是i2c的地址，0xff是nvp寄存器的地址，0x00是向寄存器写值(选bank0)	
			gpio_i2c_write(0x60,(0x0c+ad.ch),ad.brightness);//亮度
			gpio_i2c_write(0x60,(0x10+ad.ch),ad.contrast);//对比度
			gpio_i2c_write(0x60,(0x40+ad.ch),ad.hue);//色度
			gpio_i2c_write(0x60,(0x3c+ad.ch),ad.saturation);//饱合度
			break;
				
		}
		case IOC_VDEC_SET_AUDIO_PARM:
		
		{
			
			vdec_audio_volume_parm parm;
			if(copy_from_user(&parm,arg,sizeof(vdec_audio_volume_parm)))
			{
				printk("error\n");

				 return -1;
			}
			set_audio_parm(0x60,&parm);
			break;	



		}

#if 0
        case IOC_VIDEO_GET_VIDEO_MODE:
		case IOC_VIDEO_SET_MOTION:
        case IOC_VIDEO_GET_MOTION:
		case IOC_VIDEO_SET_MOTION_EN:
		case IOC_VIDEO_SET_MOTION_SENS:
		case IOC_VIDEO_SET_MOTION_TRACE:
        case IOC_VIDEO_GET_VIDEO_LOSS:
		case IOC_VIDEO_GET_IMAGE_ADJUST:
        case IOC_AUDIO_SET_SAMPLE_RATE:
        case IOC_AUDIO_SET_AUDIO_PLAYBACK:
        case IOC_AUDIO_SET_AUDIO_DA_VOLUME:
		case IOC_AUDIO_SET_BRIGHTNESS:
		case IOC_AUDIO_SET_CONTRAST:
		case IOC_AUDIO_SET_HUE:
		case IOC_AUDIO_SET_SATURATION:
		case IOC_AUDIO_SET_SHARPNESS:
		case IOC_AUDIO_SET_AUDIO_MUTE:
		case IOC_AUDIO_SET_LIVE_CH:
		case IOC_AUDIO_SET_PB_CH:
#endif
		default:
            //printk("drv:invalid nc decoder ioctl cmd[%x]\n", cmd);
			break;
	}
	return 0;
}

static struct file_operations vdec_fops = {
	.owner      = THIS_MODULE,
    //.ioctl      = vdec_ioctl,
    .unlocked_ioctl	= vdec_ioctl,
	.open       = vdec_open,
	.release    = vdec_close
};

static struct miscdevice vdec_dev = {
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "nc_vdec",
	.fops  		= &vdec_fops,
};

int chip_id[2000];
static int __init vdec_module_init(void)
{
	int ret = 0, i = 0;
    unsigned char i2c_addr;

	ret = misc_register(&vdec_dev);

   	if (ret)
	{
		printk("ERROR: could not register NC Decoder devices:%#x \n",i);		
	}
	
	printk("NVP1918 Test Driver \n");
	


	for(i=0;i<2;i++)
	{
		//printk("i:%d\n",/*vdec_slave_addr[i]*/i);
		//gpio_i2c_write( NVP1918+i, 0xFF, 0x01);
		//chip_id = gpio_i2c_read( NVP1918+i, 0xF4);
		chip_id[i] = check_id( vdec_slave_addr[i] );
		if( (chip_id[i] != NVP1918_R0 )  && 
			(chip_id[i] != NVP1118B_R0 ) &&
			(chip_id[i] != NVP1918_R1 )  &&
			(chip_id[i] != NVP1118B_R1)  &&
			(chip_id[i] != NVP1918_R2 )  &&
			(chip_id[i] != NVP1118B_R2 ) &&
			(chip_id[i] != NVP1914_R2 )  &&
			(chip_id[i] != NVP1114B_R2 ) )
		{
			printk("Blade Device ID Error... %x\n", chip_id[i]);
		}
		else
		{
			printk("Blade Device (0x%x) ID OK... %x\n", vdec_slave_addr[i], chip_id[i]);
			vdec_cnt++;
			//break;
		}
	}


#ifdef NVP1118B
	printk("NVP1118B Count = %x\n", vdec_cnt);
	//nvp1918_720h_nt();//yk del20130412
	nvp1918_720h_pal();//yk change
#else
	printk("NVP1918 Count = %x\n", vdec_cnt);
	nvp1918_960h_pal();
#endif
	//nvp1918_720h_pal();
	//nvp1918_960h_nt();
	return 0;
}



static void __exit vdec_module_exit(void)
{
	misc_deregister(&vdec_dev);	
}

module_init(vdec_module_init);
module_exit(vdec_module_exit);

MODULE_LICENSE("GPL");
