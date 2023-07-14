/***********************************************************************************************

    solo1_asic_vid.cpp

    WebTV Networks Inc. SOLO1 ASIC (Video)

    This ASIC controls most of the I/O on the 2nd generation WebTV hardware.

    This implementation is based off of both the archived technical specifications, as well as
    the various reverse-engineering efforts of the WebTV community.

    The technical specifications that this implementation is based on can be found here:
    http://wiki.webtv.zone/misc/SOLO1/SOLO1_ASIC_Spec.pdf

************************************************************************************************/

#ifndef MAME_MACHINE_SOLO1_ASIC_VID_H
#define MAME_MACHINE_SOLO1_ASIC_VID_H

#pragma once

#include "cpu/mips/mips3.h"

class solo1_asic_vid_device : public device_t, public device_video_interface
{
public:
	// construction/destruction
	solo1_asic_vid_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
    
    uint32_t reg_vid_r(offs_t offset);
    void reg_vid_w(offs_t offset, uint32_t data);
    
    uint32_t reg_pot_r(offs_t offset);
    void reg_pot_w(offs_t offset, uint32_t data);
    
    uint32_t screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
    
    void hsync_callback(s32 param);
    void vsync_callback(s32 param);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;

private:
    required_device<mips3_device> m_hostcpu;
    
    void fillbitmap_yuy16(bitmap_yuy16 &bitmap, uint8_t yval, uint8_t cr, uint8_t cb);
    uint16_t screen_height;

    uint32_t m_pot_vstart; // Vertical starting line
    uint32_t m_pot_vsize; // Vertical size
    uint32_t m_pot_blnkcol; // Blanking color
    uint32_t m_pot_hstart; // Horizontal starting pixel
    uint32_t m_pot_hsize; // Horizontal size
    uint32_t m_pot_cntl;
    uint32_t m_pot_hintline; // Line where the interrupt happened
    uint32_t m_pot_int_enable;
    uint32_t m_pot_int_status;
    uint32_t m_pot_cline; // Current line

    uint32_t m_vid_cstart;
    uint32_t m_vid_csize;
    uint32_t m_vid_ccount;
    uint32_t m_vid_nstart; // The address of the next video DMA
    uint32_t m_vid_nsize; // The number of bytes to be transferred for the next DMA
    uint32_t m_vid_dmacntl;
    uint32_t m_vid_int_status;
    uint32_t m_vid_int_enable;
    uint32_t m_vid_vdata;

    uint32_t m_intstat;
    
	bitmap_yuy16 buffer;
};

DECLARE_DEVICE_TYPE(SOLO1_ASIC_VID, solo1_asic_vid_device)

#endif