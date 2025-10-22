#ifndef CLOCK_ENABLEMENT_DRIVER_H
#define CLOCK_ENABLEMENT_DRIVER_H

#include "xil_io.h"
#include "xstatus.h"
#include "xparameters_ps.h"

// SLCR (System Level Control Registers) addresses
#define SLCR_UNLOCK_ADDR    0xF8000008
#define SLCR_LOCK_ADDR      0xF8000004
#define SLCR_UNLOCK_KEY     0xDF0D
#define SLCR_LOCK_KEY       0x767B

// FPGA Clock Control Registers
#define FPGA0_CLK_CTRL      0xF8000170
#define FPGA1_CLK_CTRL      0xF8000180
#define FPGA2_CLK_CTRL      0xF8000190
#define FPGA3_CLK_CTRL      0xF80001A0

// Clock enable bit
#define FCLK_CLK_ENABLE     0x00000001

/**
 * @brief Enable specified FCLK clock from PS to PL
 *
 * This function unlocks the SLCR, enables the specified FCLK output,
 * and locks the SLCR again for safety.
 *
 * @param clk_num Clock number (0-3 for FCLK_CLK0 through FCLK_CLK3)
 * @return XST_SUCCESS if successful, XST_FAILURE if invalid clock number
 */
int enable_fclk(u8 clk_num)
{
    u32 reg_val;
    u32 clk_ctrl_addr;

    // Determine which clock control register to use
    switch(clk_num) {
        case 0:
            clk_ctrl_addr = FPGA0_CLK_CTRL;
            break;
        case 1:
            clk_ctrl_addr = FPGA1_CLK_CTRL;
            break;
        case 2:
            clk_ctrl_addr = FPGA2_CLK_CTRL;
            break;
        case 3:
            clk_ctrl_addr = FPGA3_CLK_CTRL;
            break;
        default:
            return XST_FAILURE;  // Invalid clock number
    }

    // Unlock SLCR to allow modifications
    Xil_Out32(SLCR_UNLOCK_ADDR, SLCR_UNLOCK_KEY);

    // Read current value of clock control register
    reg_val = Xil_In32(clk_ctrl_addr);

    // Set bit 0 to enable the clock (preserve other settings)
    reg_val |= FCLK_CLK_ENABLE;

    // Write back to enable the clock
    Xil_Out32(clk_ctrl_addr, reg_val);

    // Lock SLCR to prevent accidental modifications
    Xil_Out32(SLCR_LOCK_ADDR, SLCR_LOCK_KEY);

    return XST_SUCCESS;
}

/**
 * @brief Disable specified FCLK clock from PS to PL
 *
 * @param clk_num Clock number (0-3 for FCLK_CLK0 through FCLK_CLK3)
 * @return XST_SUCCESS if successful, XST_FAILURE if invalid clock number
 */
int disable_fclk(u8 clk_num)
{
    u32 reg_val;
    u32 clk_ctrl_addr;

    // Determine which clock control register to use
    switch(clk_num) {
        case 0:
            clk_ctrl_addr = FPGA0_CLK_CTRL;
            break;
        case 1:
            clk_ctrl_addr = FPGA1_CLK_CTRL;
            break;
        case 2:
            clk_ctrl_addr = FPGA2_CLK_CTRL;
            break;
        case 3:
            clk_ctrl_addr = FPGA3_CLK_CTRL;
            break;
        default:
            return XST_FAILURE;  // Invalid clock number
    }

    // Unlock SLCR to allow modifications
    Xil_Out32(SLCR_UNLOCK_ADDR, SLCR_UNLOCK_KEY);

    // Read current value of clock control register
    reg_val = Xil_In32(clk_ctrl_addr);

    // Clear bit 0 to disable the clock (preserve other settings)
    reg_val &= ~FCLK_CLK_ENABLE;

    // Write back to disable the clock
    Xil_Out32(clk_ctrl_addr, reg_val);

    // Lock SLCR to prevent accidental modifications
    Xil_Out32(SLCR_LOCK_ADDR, SLCR_LOCK_KEY);

    return XST_SUCCESS;
}

#endif //CLOCK_ENABLEMENT_DRIVER_H
