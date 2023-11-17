#include "ucregisters.h"     

#ifndef SDCARD_H
#define SDCARD_H 

uint16_t timeout;
enum _card_type{MMC, SDSC, SDHC} g_card_type;
enum sdcard_err{
  sdcard_goodec = 0, sdcard_idle = 0x01, sdcard_timeout = 0x80,
  sdcard_illegal_cmd = 0x04 };

#define GO_IDLE_STATE 0
#define SEND_IF_COND 8
#define SET_BLOCKLEN 16
#define READ_SINGLE_BLOCK 17
#define WRITE_BLOCK 24
#define SEND_APP_OP_COND 41
#define APP_CMD 55
#define READ_OCR 58

void send_sdcard_command(uint8_t command, uint32_t sd_data, uint8_t sd_crc);
sdcard_err sdcard_init();                    
sdcard_err sdcard_read_byte(uint32_t addr, uint8_t* data);
sdcard_err sdcard_read_sector(uint32_t sector_number, uint8_t* data);
sdcard_err sdcard_read_data(uint32_t addr, uint16_t size, uint8_t* data);
sdcard_err sdcard_write_sector(uint32_t sector_number, uint8_t* data);
sdcard_err sdcard_write_byte(uint32_t addr, uint8_t &data);
sdcard_err sdcard_write_data(uint32_t addr, uint16_t size, uint8_t *data);
sdcard_err sdcard_get_r1();
sdcard_err sdcard_get_r7();
sdcard_err sdcard_go_idle_state();
sdcard_err sdcard_send_if_cond();
sdcard_err sdcard_send_app_cmd();
sdcard_err sdcard_sd_send_op_cond();
sdcard_err sdcard_read_ocr(uint8_t* _ocr_byte_3);
sdcard_err sdcard_set_blocklen();
void sdcard_select();
void sdcard_deselect();

#endif  //SDCARD_H
