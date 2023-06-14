#define SS 10
#define MOSI 11
#define SCK 13

void setup() {
  Serial.begin(9600);  
  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI,INPUT);
  pinMode(SCK, INPUT);
}
uint8_t data = 0;
uint8_t MOSI_Data;
uint8_t SCK_State;
uint8_t i = 0;

void loop(){
  while(i < 8)
  {
    SCK_State = digitalRead(SCK);
    if(SCK_State == 1){
      MOSI_Data = digitalRead(MOSI);
      data = data << 1;
      data = data | MOSI_Data;
      i++;
      while(SCK_State == 1) SCK_State = digitalRead(SCK);
    } 
  }
  if(i == 8)
  {
    Serial.print("Received data: ");
    Serial.println(data,BIN);
    i = 0;
    data = 0;
    MOSI_Data = 0;
  }
}