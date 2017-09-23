const int CLK_DIO = 7;
const int DATA_DIO = 8;
const int LATCH_DIO = 4;



//SEGMENTS contains the segment selector 0b1111XYZW
const int SEGMENTS[] = {0b11110001, 0b11110010, 0b11110100, 0b11111000};

//DIGITS contains the actual digits where DIGITS[0]
//will be the bit string to draw a 0 on the 7-segment display
const int DIGITS[] = {0b11000000, 0b11111001,0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b00000000, 0b10011000};


void SetupPins()
{
//Make sure that we can write to CLK_DIO, DATA_DIO, and LATCH_DIO
pinMode(CLK_DIO, OUTPUT);
pinMode(DATA_DIO, OUTPUT);
pinMode(LATCH_DIO, OUTPUT);

}


void SetSegment(int segment, int digit)
{
//Set <segment>'s value to <digit>
int mask;
int mask1;

digitalWrite(LATCH_DIO, LOW);

for (int i = 7; i >= 0; i--){
mask1 = 1 << i;
int digit_mask = DIGITS[digit] & mask1;
digitalWrite(DATA_DIO, digit_mask);
digitalWrite(CLK_DIO, LOW);
digitalWrite(CLK_DIO, HIGH);
}

for (int i = 7; i >= 0; i--){
mask = 1 << i;
int segment_mask = SEGMENTS[segment] & mask;
digitalWrite(DATA_DIO, segment_mask);
digitalWrite(CLK_DIO, LOW);
digitalWrite(CLK_DIO, HIGH);
}

digitalWrite(LATCH_DIO, HIGH);
}



const int segment_limit = sizeof(SEGMENTS) / sizeof(int);
const int digit_limit = sizeof(DIGITS) / sizeof(int);

int values[] = {0, 0, 0, 0};
int value = 0;

void setup() {
SetupPins();
Serial.begin(115200);
Serial.print("Enter value: ");
}

void loop()
{
int tmp = value;
/*if (Serial && Serial.available() > 0) {
String input = Serial.readString();

char buf[10];

if (value > 9999 || value < 0) {
value = 1234;
}*/

values[0] = value / 1000;
value -= values[0] * 1000;
values[1] = value / 100;
value -= values[1] * 100;
values[2] = value / 10;
value -= values[2] * 10;
values[3] = value;

//sprintf(buf, "%d %d %d %d", values[0], values[1], values[2], values[3]);

// Serial.print("\nDisplay set to ");
// Serial.print(buf);
// Serial.print("\nEnter value: ");

for (int i = 0;i < 4;i++) {
if (i >= segment_limit) {
break;
}
if (values[i] < digit_limit) {
SetSegment(i, values[i]);
}
}

delay(10);

value = tmp;
value++;
if(value>9999) value = 0;

}
