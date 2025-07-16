/**
 * Based on https://gist.github.com/racerxdl/c9a592808acdd9cd178e6e97c83f8baf
 * which was based on: https://github.com/jaromir-sukuba/efm8prog/
 Use his SW to program EFM8 using arduino.
**/

// GPIO is manipulated through PORT mappings for better speed.
// Flashes EFM8 at about 10kB/s
// Baud rate: 1000000

// Digital pin 0 on MKR WiFi 1010
#define C2D 0
// #define C2D_PORT PORTA
// #define C2D_PIN  22

// Digital pin 1 on MKR WiFi 1010
#define C2CK 1
// #define C2CK_PORT PORTA
// #define C2CK_PIN  23

#define LED LED_BUILTIN

#define INBUSY   0x02
#define OUTREADY 0x01

static void c2_send_bits (unsigned char data, unsigned char len);
static unsigned char c2_read_bits (unsigned char len);

void c2_rst (void);
void c2_write_addr (unsigned char addr);
static unsigned char c2_read_addr (void);
static unsigned char c2_read_data (void);
static void c2_write_data (unsigned char addr);

unsigned char c2_init_PI (void);
unsigned char c2_read_flash_block (unsigned int addr, unsigned char * data, unsigned char len);
static unsigned char c2_poll_bit_low (unsigned char mask);
static unsigned char c2_poll_bit_high (unsigned char mask);
unsigned char c2_write_flash_block (unsigned int addr, unsigned char * data, unsigned char len);
unsigned char c2_erase_device (void);


void c2_rst() {
  digitalWrite(C2CK, LOW);
  // C2CK_PORT &= ~(1<<C2CK_PIN);
  delayMicroseconds(50);
  digitalWrite(C2CK, HIGH);
  // C2CK_PORT |= (1<<C2CK_PIN);
  delayMicroseconds(10);
}

// #define c2_pulse_clk()       \
//   C2CK_PORT &= ~(1<<C2CK_PIN); \
//   C2CK_PORT |= (1<<C2CK_PIN);

#define c2_pulse_clk()\
  digitalWrite(C2CK, LOW); \
  digitalWrite(C2CK, HIGH);


static unsigned char c2_read_bits (unsigned char len) {
  unsigned char i, data, mask;
  mask = 0x01 << (len-1);
  data = 0;
  pinMode(C2D, INPUT);
  // PINE &= (1<<C2D_PIN);
  for (i=0;i<len;i++) {
    c2_pulse_clk();
    data = data >> 1;
    // if (PINE & (1<<C2D_PIN)) {
    if (digitalRead(C2D)) {
      data = data | mask;
    }
  }
  pinMode(C2D, OUTPUT);

  return data;
}

static void c2_send_bits (unsigned char data, unsigned char len) {
  unsigned char i;
  pinMode(C2D, OUTPUT);
  for (i=0;i<len;i++) {
    if (data&0x01) {
      digitalWrite(C2D, HIGH);
      // C2D_PORT |= (1<<C2D_PIN);
    } else {
      digitalWrite(C2D, LOW);
      // C2D_PORT &= ~(1<<C2D_PIN);
    }
    c2_pulse_clk();
    data = data >> 1;
  }
}

static void c2_write_data (unsigned char data) {
  unsigned char retval;
  c2_send_bits(0x0, 1);
  c2_send_bits(0x1, 2);
  c2_send_bits(0x0, 2);
  c2_send_bits(data, 8);
  retval = 0;
  while (retval == 0) {
    retval = c2_read_bits(1);
  }
  c2_send_bits(0x0, 1);
}

static unsigned char c2_poll_bit_high (unsigned char mask) {
  unsigned char retval;
  retval = c2_read_addr();
  while ((retval&mask)==0) retval = c2_read_addr();
}

static unsigned char c2_poll_bit_low (unsigned char mask) {
  unsigned char retval;
  retval = c2_read_addr();
  while (retval&mask) retval = c2_read_addr();
}

unsigned char c2_read_flash_block (unsigned int addr, unsigned char * data, unsigned char len) {
  unsigned char retval,i;
  c2_write_addr(0xB4);
  c2_write_data(0x06);
  c2_poll_bit_low(INBUSY);
  c2_poll_bit_high(OUTREADY);
  retval = c2_read_data();
  c2_write_data(addr>>8);
  c2_poll_bit_low(INBUSY);
  c2_write_data(addr&0xFF);
  c2_poll_bit_low(INBUSY);
  c2_write_data(len);
  c2_poll_bit_low(INBUSY);
  c2_poll_bit_high(OUTREADY);
  retval = c2_read_data();
  for (i=0;i<len;i++) {
    c2_poll_bit_high(OUTREADY);
    retval = c2_read_data();
    data[i] = retval;
  }
  return i;
}

unsigned char c2_write_flash_block (unsigned int addr, unsigned char * data, unsigned char len) {
  unsigned char retval,i;
  c2_write_addr(0xB4);
  c2_write_data(0x07);
  c2_poll_bit_low(INBUSY);
  c2_poll_bit_high(OUTREADY);
  retval = c2_read_data();
  c2_write_data(addr>>8);
  c2_poll_bit_low(INBUSY);
  c2_write_data(addr&0xFF);
  c2_poll_bit_low(INBUSY);
  c2_write_data(len);
  c2_poll_bit_low(INBUSY);
  c2_poll_bit_high(OUTREADY);
  retval = c2_read_data();
  for (i=0;i<len;i++) {
    c2_write_data(data[i] );
    c2_poll_bit_low(INBUSY);
  }
  c2_poll_bit_high(OUTREADY);
}

unsigned char c2_erase_device (void) {
  unsigned char retval;
  c2_write_addr(0xB4);
  c2_write_data(0x03);
  c2_poll_bit_low(INBUSY);
  c2_poll_bit_high(OUTREADY);
  retval = c2_read_data();
  c2_write_data(0xDE);
  c2_poll_bit_low(INBUSY);
  c2_write_data(0xAD);
  c2_poll_bit_low(INBUSY);
  c2_write_data(0xA5);
  c2_poll_bit_low(INBUSY);
  c2_poll_bit_high(OUTREADY);
  retval = c2_read_data();
}

unsigned char c2_write_sfr (unsigned char addr, unsigned char val) {
  unsigned char retval;
  c2_write_addr(0xB4);
  c2_write_data(0x0A);
  c2_poll_bit_low(INBUSY);
  c2_poll_bit_high(OUTREADY);
  retval = c2_read_data();
  c2_write_data(addr);
  c2_poll_bit_low(INBUSY);
  c2_write_data(0x1);
  c2_poll_bit_low(INBUSY);
  c2_write_data(val);
  c2_poll_bit_low(INBUSY);
}

unsigned char c2_init_PI (void) {
  c2_rst();
  c2_write_addr(0x02);
  c2_write_data(0x02);
  c2_write_data(0x04);
  c2_write_data(0x01);
  return 0;
}

unsigned char c2_init_PI_sfr (void) {
  c2_rst();
  c2_write_addr(0x02);
  c2_write_data(0x02);
  c2_write_data(0x04);
  c2_write_data(0x01);

  // set up SFRs
  delay(25);
  c2_write_sfr(0xff, 0x80);
  delay(1);
  c2_write_sfr(0xef, 0x02);
  delay(1);
  c2_write_sfr(0xA9, 0x00);
  return 0;
}

static unsigned char c2_read_data() {
  unsigned char retval;
  c2_send_bits(0x0, 1);
  c2_send_bits(0x0, 2);
  c2_send_bits(0x0, 2);
  retval = 0;
  while (retval == 0) {
    retval = c2_read_bits(1);
  }
  retval = c2_read_bits(8);
  c2_send_bits(0x0, 1);
  return retval;
}

static unsigned char c2_read_addr() {
  unsigned char retval;
  c2_send_bits(0x0, 1);
  c2_send_bits(0x2, 2);
  retval = c2_read_bits(8);
  c2_send_bits(0x0, 1);
  return retval;
}

void c2_write_addr(unsigned char addr) {
  c2_send_bits(0x0,1);
  c2_send_bits(0x3,2);
  c2_send_bits(addr,8);
  c2_send_bits(0x0,1);
}


// ----------------------------------------------------------------------
//
//  INITIALISATION
//

void setup()
{
  // Serial communications with host PC.
  Serial.begin(115200);
  Serial.print("> ");
  Serial.flush();

  pinMode(C2D, OUTPUT);
  pinMode(C2CK, OUTPUT);
  digitalWrite(C2CK, HIGH);
  // C2CK_PORT |= (1<<C2CK_PIN);

  digitalWrite(LED, LOW);
}


// ----------------------------------------------------------------------
//
//  MAIN LOOP
//

void loop()
{
  while (Serial.available() > 0) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    Serial.println(line);

    // Split on command.
    if (line == "unbrick") {
      Serial.println("Attempting to unbrick...");
      c2_init_PI();
    } else if (line == "check") {
      Serial.println("Check: ???");
    } else if (line == "erase") {
      Serial.println("Erasing...");
      c2_erase_device();
    } else
      Serial.println("Unknown command");

    Serial.print("> ");
    Serial.flush();
  }
}
