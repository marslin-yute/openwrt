include $(TOPDIR)/rules.mk

PKG_NAME:=ubus
PKG_VERSION:=2011-02-26
PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://nbd.name/luci2/ubus.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=6cf4326987c78ecc340930b48fce5b324c8d6a4d
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/ubus
  SECTION:=luci2
  CATEGORY:=LuCI2
  SUBMENU:=System
  DEPENDS:=+libubus +libblobmsg-json +ubusd
  TITLE:=OpenWrt RPC client utility
endef

define Package/ubusd
  SECTION:=luci2
  CATEGORY:=LuCI2
  SUBMENU:=System
  TITLE:=OpenWrt RPC daemon
endef

define Package/libubus
  SECTION:=luci2
  CATEGORY:=LuCI2
  SUBMENU:=Libraries
  DEPENDS:=+libubox
  TITLE:=OpenWrt RPC client library
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include

define Package/ubus/install
	$(INSTALL_DIR) $(1)/bin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/ubus $(1)/bin/
endef

define Package/ubusd/install
	$(INSTALL_DIR) $(1)/sbin
	$(CP) $(PKG_INSTALL_DIR)/usr/sbin/ubusd $(1)/sbin/
endef

define Package/libubus/install
	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/lib/
endef

$(eval $(call BuildPackage,ubus))
$(eval $(call BuildPackage,ubusd))
$(eval $(call BuildPackage,libubus))

