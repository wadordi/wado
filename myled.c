// SPDX-License-Identifer: GPL-3.0
/*
 * Copyright (C) 2020 Tomoki.Terasawa. All rights reserved 
  */
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/delay.h>

MODULE_AUTHOR("Ryuichi Ueda & Tomoki Terasawa");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;


static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
	char c;
	int a,i;
	if(copy_from_user(&c,buf,sizeof(char)))
	return -EFAULT;

	//printk(KERN_INFO "receive %c\n",c);
	
	if(c == '0'){
		gpio_base[10] = 1 << 25;
		gpio_base[10] = 1 << 24;
		gpio_base[10] = 1 << 23;
		gpio_base[10] = 1 << 22;

	}
	else if(c == '1'){
		gpio_base[7] = 1 << 25;
		gpio_base[7] = 1 << 24;
		gpio_base[7] = 1 << 23;
		gpio_base[7] = 1 << 22;

	}
	else if(c == 'r'){
		for(i = 0;i < 20; i++){
		gpio_base[7] = 1 << 25;
		gpio_base[10] = 1 << 23;
		msleep(200);
		gpio_base[7] = 1 << 24;
		gpio_base[10] = 1 << 22;
		msleep(200);
		gpio_base[7] = 1 << 23;
		gpio_base[10] = 1 << 25; 
		msleep(200);
		gpio_base[7] = 1 << 22;
		gpio_base[10] = 1 << 24;
		msleep(200);
		}
		gpio_base[10] = 1 << 23;
		msleep(200);
		gpio_base[10] = 1 << 22;
	}
		
	
	else if(c == 'l'){
		for(i = 0;i < 20; i++){
		gpio_base[7] = 1 << 25;
		gpio_base[10] = 1 << 23;
		msleep(200);
		gpio_base[7] = 1 << 22;
		gpio_base[10] = 1 << 24;
		msleep(200);
		gpio_base[7] = 1 << 23;
		gpio_base[10] = 1 << 25; 
		msleep(200);
		gpio_base[7] = 1 << 24;
		gpio_base[10] = 1 << 22;
		msleep(200);
		}
		gpio_base[10] = 1 << 23;
		msleep(200);
		gpio_base[10] = 1 << 24;
	}
	else if(c == 'a' || c == 'b' || c == 'c'){
		if(c == 'a'){a = 10;}
		if(c == 'b'){a = 30;}
		if(c == 'c'){a = 60;}
		for(i = 0; i < a; i++){
		
		gpio_base[7] = 1 << 25;
		gpio_base[10] = 1 << 23;
		msleep(240);
		gpio_base[7] = 1 << 24;
		gpio_base[10] = 1 << 22;
		msleep(240);
		gpio_base[7] = 1 << 23;
		gpio_base[10] = 1 << 25; 
		msleep(240);
		gpio_base[7] = 1 << 22;
		gpio_base[10] = 1 << 24;
		msleep(240);
		}
		for(i = 0;i < 100; i++){
		gpio_base[7] = 1 << 25;
		gpio_base[7] = 1 << 24;
		gpio_base[7] = 1 << 23;
		gpio_base[7] = 1 << 22;
		msleep(50);

		gpio_base[10] = 1 << 25;
		gpio_base[10] = 1 << 24;
		gpio_base[10] = 1 << 23;
		gpio_base[10] = 1 << 22;
		msleep(50);
		}
		
	}
	return 1;
}
static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t*pos)
{
	int size = 0;
	 char sushi[] = {'s', 'u', 's', 'h', 'i' ,0x0A};
	 if(copy_to_user(buf+size,(const char *)sushi,sizeof(sushi))){
		 printk( KERN_INFO "sushi : copy_to_user failed\n");
	return -EFAULT;
	 }
	 size += sizeof(sushi);
 	 return size;
}

static struct file_operations led_fops = {
	.owner = THIS_MODULE,
	.write = led_write,
	.read = sushi_read
};
static int __init init_mod(void)
{
	int retval;

	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return retval;
	}
	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));

	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d\n",MAJOR(dev),MINOR(dev));
		return	retval;
	}

	cls = class_create(THIS_MODULE,"myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
                return PTR_ERR(cls);
	}

	device_create(cls, NULL, dev, NULL, "myled%d", MINOR(dev));
	
	gpio_base = ioremap_nocache(0xfe200000, 0xA0);

	const u32 led_1 =25;
	const u32 index_1 = led_1/10;
	const u32 shift_1 = (led_1%10)*3;
	const u32 mask_1 = ~(0x7 << shift_1);
	gpio_base[index_1] = (gpio_base[index_1] & mask_1) | (0x1 << shift_1);

	
	const u32 led_2 =24;
	const u32 index_2 = led_2/10;
	const u32 shift_2 = (led_2%10)*3;
	const u32 mask_2 = ~(0x7 << shift_2);
	gpio_base[index_2] = (gpio_base[index_2] & mask_2) | (0x1 << shift_2);

	const u32 led_3 =23;
	const u32 index_3 = led_3/10;
	const u32 shift_3 = (led_3%10)*3;
	const u32 mask_3 = ~(0x7 << shift_3);
	gpio_base[index_3] = (gpio_base[index_3] & mask_3) | (0x1 << shift_3);

	const u32 led_4 =22;
	const u32 index_4 = led_4/10;
	const u32 shift_4 = (led_4%10)*3;
	const u32 mask_4 = ~(0x7 << shift_4);
	gpio_base[index_4] = (gpio_base[index_4] & mask_4) | (0x1 << shift_4);

        return 0;

}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. major:%d\n",__FILE__,MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);
