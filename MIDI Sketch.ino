/* (c) Arduino MIDI Controller by Nathan Rodrigues
 * Email : nathanrodrigues2111@gmail.com
 * YouTube : https://www.youtube.com/channel/UCu7i2pUEoPFWwhd_kBC_zuA
 * Website : ??????
 *
 * Edit it however you wish, As long as you know what you are doing.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 

// include MIDI library
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();
 
// read digital pins number 2, 3, 4, 5
int pushButton2 = 2;
int pushButton3 = 3;
int pushButton4 = 4;
int pushButton5 = 5;
 
// checks if the button is pressed
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
 
// play/stop notes in relation to buttons pressed
int note2 = 0;
int note3 = 0;
int note4 = 0;
int note5 = 0;

//Analog buttons
int val = 0; //Our initial pot values. We need one for the first value and a second to test if there has been a change made. This needs to be done for all 5 pots.
int lastVal = 0;
int val2 = 0;
int lastVal2 = 0;
int val3 = 0;
int lastVal3 = 0;
int val4 = 0;
int lastVal4 = 0;
int val5 = 0;
int lastVal5 = 0;

void setup() {
  MIDI.begin(4);
  // 38400 hairless MIDI
  Serial.begin(38400);

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  pinMode(pushButton2, INPUT_PULLUP);
  pinMode(pushButton3, INPUT_PULLUP);
  pinMode(pushButton4, INPUT_PULLUP);
  pinMode(pushButton5, INPUT_PULLUP);
}
 
void loop() {
  // read state of buttons
  int buttonState2 = digitalRead(pushButton2);
  int buttonState3 = digitalRead(pushButton3);
  int buttonState4 = digitalRead(pushButton4);
  int buttonState5 = digitalRead(pushButton5);

//Digital Buttons

   // Button 2
  if (buttonState2 == LOW) {
    if (note2 == 0) {
      MIDI.sendNoteOn(63,127,1);
      note2 = 1;
    }
  } else {
    if (note2 == 1) {
      MIDI.sendNoteOff(63,0,1);
    }
    note2 = 0;
  }

   // Button 3
  if (buttonState3 == LOW) {
    if (note3 == 0) {
      MIDI.sendNoteOn(64,127,1);
      note3 = 1;
    }
  } else {
    if (note3 == 1) {
      MIDI.sendNoteOff(64,0,1);
    }
    note3 = 0;
  }

   // Button 4
  if (buttonState4 == LOW) {
    if (note4 == 0) {
      MIDI.sendNoteOn(65,127,1);
      note4 = 1;
    }
  } else {
    if (note4 == 1) {
      MIDI.sendNoteOff(65,0,1);
    }
    note4 = 0;
  }

   // Button 5
  if (buttonState5 == LOW) {
    if (note5 == 0) {
      MIDI.sendNoteOn(66,127,1);
      note5 = 1;
    }
  } else {
    if (note5 == 1) {
      MIDI.sendNoteOff(66,0,1);
    }
    note5 = 0;
  }



  //Analog Potentionmeter

  val = analogRead(0)/8;   // Divide by 8 to get range of 0-127 for midi
   if (val != lastVal) // If the value does not = the last value the following command is made. This is because the pot has been turned. Otherwise the pot remains the same and no midi message is output.
   {
   MIDImessage(176,1,val);}         / // 176 = CC command, 2 = Which Control, val = value read from Potentionmeter 1
   lastVal = val;

   val2 = analogRead(1)/8;   // Divide by 8 to get range of 0-127 for midi
   if (val2 != lastVal2) 
   {
   MIDImessage(176,2,val2);}         // 176 = CC command, 2 = Which Control, val = value read from Potentionmeter 2
   lastVal2 = val2;
   
   val3 = analogRead(2)/8;   // Divide by 8 to get range of 0-127 for midi
   if (val3 != lastVal3) 
   {
   MIDImessage(176,3,val3);}         // 176 = CC command, 3 = Which Control, val = value read from Potentionmeter 3
   lastVal3 = val3;

    val4 = analogRead(3)/8;   // Divide by 8 to get range of 0-127 for midi
   if (val4 != lastVal4) 
   {
   MIDImessage(176,4,val4);}         // 176 = CC command, 4 = Which Control, val = value read from Potentionmeter 4
   lastVal4 = val4;
   
   val5 = analogRead(4)/8;   // Divide by 8 to get range of 0-127 for midi
   if (val5 != lastVal5) 
   {
   MIDImessage(176,5,val5);}         // 176 = CC command, 5 = Which Control, val = value read from Potentionmeter 5
   lastVal5 = val5;
delay(10); //here we add a short delay to help prevent slight fluctuations, knocks on the pots etc. Adding this helped to prevent my pots from jumpin up or down a value when slightly touched or knocked.
}




void MIDImessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   Serial.write(command);
   Serial.write(data1);
   Serial.write(data2);
}
