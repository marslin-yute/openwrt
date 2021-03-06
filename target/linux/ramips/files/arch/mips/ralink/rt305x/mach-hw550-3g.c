/*
 *  Aztech HW550-3G board support
 *
 *  Copyright (C) 2011 Layne Edwards <ledwards76@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/physmap.h>

#include <asm/mach-ralink/machine.h>
#include <asm/mach-ralink/dev-gpio-buttons.h>
#include <asm/mach-ralink/dev-gpio-leds.h>
#include <asm/mach-ralink/rt305x.h>
#include <asm/mach-ralink/rt305x_regs.h>

#include "devices.h"

#define HW550_3G_GPIO_LED_USB		8
#define HW550_3G_GPIO_LED_3G_STAT	11
#define HW550_3G_GPIO_LED_3G_TOGGLE	12
#define HW550_3G_GPIO_LED_WPS		14

#define HW550_3G_GPIO_BUTTON_RESET	10
#define HW550_3G_GPIO_BUTTON_3G		7
#define HW550_3G_GPIO_BUTTON_WPS	0

#define HW550_3G_BUTTONS_POLL_INTERVAL	20

#ifdef CONFIG_MTD_PARTITIONS
static struct mtd_partition hw550_3g_partitions[] = {
	{
		.name	= "u-boot",
		.offset	= 0,
		.size	= 0x030000,
		.mask_flags = MTD_WRITEABLE,
	}, {
		.name	= "config",
		.offset	= 0x030000,
		.size	= 0x010000,
		.mask_flags = MTD_WRITEABLE,
	}, {
		.name	= "factory",
		.offset	= 0x040000,
		.size	= 0x010000,
		.mask_flags = MTD_WRITEABLE,
	}, {
		.name	= "kernel",
		.offset	= 0x050000,
		.size	= 0x180000,
	}, {
		.name	= "rootfs",
		.offset	= 0x1d0000,
		.size	= 0x580000,
	}, {
		.name	= "user",
		.offset	= 0x750000,
		.size	= 0x0b0000,
	}, {
		.name	= "firmware",
		.offset	= 0x050000,
		.size	= 0x700000,
	}
};
#endif /* CONFIG_MTD_PARTITIONS */

static struct physmap_flash_data hw550_3g_flash_data = {
#ifdef CONFIG_MTD_PARTITIONS
	.nr_parts	= ARRAY_SIZE(hw550_3g_partitions),
	.parts		= hw550_3g_partitions,
#endif
};

static struct gpio_led hw550_3g_leds_gpio[] __initdata = {
	{
		.name		= "hw550-3g:green:usb",
		.gpio		= HW550_3G_GPIO_LED_USB,
		.active_low	= 1,
	}, {
		.name		= "hw550-3g:green:3g-stat",
		.gpio		= HW550_3G_GPIO_LED_3G_STAT,
		.active_low	= 1,
	}, {
		.name		= "hw550-3g:green:3g-toggle",
		.gpio		= HW550_3G_GPIO_LED_3G_TOGGLE,
		.active_low	= 1,
	}, {
		.name		= "hw550-3g:green:wps",
		.gpio		= HW550_3G_GPIO_LED_WPS,
		.active_low	= 1,
	}
};

static struct gpio_button hw550_3g_gpio_buttons[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.threshold	= 3,
		.gpio		= HW550_3G_GPIO_BUTTON_RESET,
		.active_low	= 1,
	}, {
		.desc		= "3g",
		.type		= EV_KEY,
		.code		= BTN_1,
		.threshold	= 3,
		.gpio		= HW550_3G_GPIO_BUTTON_3G,
		.active_low	= 1,
	}, {
		.desc		= "wps",
		.type		= EV_KEY,
		.code		= KEY_WPS_BUTTON,
		.threshold	= 3,
		.gpio		= HW550_3G_GPIO_BUTTON_WPS,
		.active_low	= 1,
	}
};

static void __init hw550_3g_init(void)
{
	rt305x_gpio_init(RT305X_GPIO_MODE_GPIO << RT305X_GPIO_MODE_UART0_SHIFT);

	rt305x_register_flash(0, &hw550_3g_flash_data);
	rt305x_register_ethernet();
	ramips_register_gpio_leds(-1, ARRAY_SIZE(hw550_3g_leds_gpio),
				  hw550_3g_leds_gpio);
	ramips_register_gpio_buttons(-1, HW550_3G_BUTTONS_POLL_INTERVAL,
				     ARRAY_SIZE(hw550_3g_gpio_buttons),
				     hw550_3g_gpio_buttons);
	rt305x_register_wifi();
	rt305x_register_wdt();
}

MIPS_MACHINE(RAMIPS_MACH_HW550_3G, "HW550-3G", "Aztech HW550-3G",
	     hw550_3g_init);
