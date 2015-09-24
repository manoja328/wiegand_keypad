/* Read RFID keypad using Wiegand protocal
 which has vcc , gnd
 D0 and D1 */
void setup()
{
    pinMode(8,INPUT); //d0
    pinMode(9,INPUT); // d1
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    Serial.begin(9600);

}

char KEY_PAD[] ="0123456789EN";
char MY_PASS[6] ="12345";
char mytemp[6];
unsigned char pass_cnt=0;
unsigned char rd,prevrd=3;
unsigned char readno=0;
char bit_pos=7; // make this char not unsigned char

void loop()
{
    rd= digitalRead(8)*2 + digitalRead(9);
    if (rd == 3 && prevrd !=3 )
        Serial.println("idle");
    else if (prevrd==3 && rd == 1)
    {
        bit_pos--;
        Serial.println("0");
    }
    else if (prevrd==3 && rd == 2)
    {
        readno = readno |  1 << bit_pos;
        bit_pos--;
        Serial.println("1");
    }
    prevrd=rd;
    if (bit_pos < 0)
    {
        bit_pos=7;
        Serial.print("No: ");
        Serial.print(readno);
        Serial.print(" ---->> ");
        Serial.println(KEY_PAD[readno & 0x0F]);
        mytemp[pass_cnt]=KEY_PAD[readno & 0x0F];
        pass_cnt++;
        if (pass_cnt > 4)
        {
            pass_cnt=0;
            Serial.println(mytemp);
            if ( strcmp(mytemp,MY_PASS) == 0)
            {
                Serial.println("Successfull entry!!");
                digitalWrite(10,LOW);
                delay(500);
                digitalWrite(10,HIGH);
                delay(500);
                digitalWrite(10,LOW);
            }
            else
            {
                Serial.println("Wrong password...");
                digitalWrite(11,LOW);
                delay(500);
                digitalWrite(11,HIGH);
                delay(500);
                digitalWrite(11,LOW);
            }
        }
        readno=0;
    }


}