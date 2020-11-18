#include "config.h"
#include "tic.h"
#include "7seg.h"
TTGOClass *ttgo;
int n=3;

int numbers[3][3];
int posX[3];

int boxSize=64;
int space=5;
int start=19;

bool player=0;
bool gameover=0;
bool irq = false;

void setup()
{
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    ttgo->tft->fillScreen(TFT_WHITE);
    ttgo->tft->setFreeFont(&DSEG7_Classic_Regular_40);
    ttgo->tft->setTextColor(TFT_BLACK);

  
   
   // ttgo->tft->drawString("T-Watch Touch Test", 62, 90);

   for(int i=0;i<n;i++)
posX[i]=(start+(i*boxSize)+(space*i));

ttgo->tft->fillRect(posX[1]-5,posX[0],4,206,TFT_BLACK);
 ttgo->tft->fillRect(posX[2]-5,posX[0],4,206,TFT_BLACK);

 ttgo->tft->fillRect(posX[0],posX[1]-5,206,4,TFT_BLACK);
 ttgo->tft->fillRect(posX[0],posX[2]-5,206,4,TFT_BLACK);



   for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){
    //ttgo->tft->fillRect(posX[i],posX[j],boxSize,boxSize,TFT_BLUE);
    numbers[j][i]=0;
    }

    
    pinMode(AXP202_INT, INPUT_PULLUP);
    attachInterrupt(AXP202_INT, [] {
        irq = true;
    }, FALLING);

    //!Clear IRQ unprocessed  first
    ttgo->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ | AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_IRQ, true);
    ttgo->power->clearIRQ();

   
}

void loop()
{
    int16_t x, y;
    if(gameover==0)
    if (ttgo->getTouch(x, y)) {
        
      for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
          {
            if(x>posX[j] && x<posX[j]+boxSize && y>posX[i] && y<posX[i]+boxSize )
            {
              if(numbers[j][i]==0){ 
               ttgo->tft->pushImage(posX[j],posX[i],boxSize,boxSize,tic[player]);
                if(player==0)
                numbers[j][i]=1;
                    if(player==1)
                numbers[j][i]=2;
                //ttgo->tft->drawString(String(numbers[j][i]),posX[j],posX[i]);
                player=!player;
            
                x=0;
                y=0;
              
              }
              
            }
            }
    }

     if (irq) {
        irq = false;
        ttgo->power->readIRQ();

        if (ttgo->power->isPEKShortPressIRQ()) {
          reset();
        }
        ttgo->power->clearIRQ(); }
    
check();
}

void reset(){
     ttgo->tft->fillScreen(TFT_WHITE);
     gameover=0;
     player=0;
     for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){
    ttgo->tft->fillRect(posX[i],posX[j],boxSize,boxSize,TFT_WHITE);
    numbers[i][j]=0;
ttgo->tft->fillRect(posX[1]-5,posX[0],4,206,TFT_BLACK);
 ttgo->tft->fillRect(posX[2]-5,posX[0],4,206,TFT_BLACK);

 ttgo->tft->fillRect(posX[0],posX[1]-5,206,4,TFT_BLACK);
 ttgo->tft->fillRect(posX[0],posX[2]-5,206,4,TFT_BLACK);
   
  
  }}

  void check()
  {
    
   for(int i=0;i<3;i++){ ///horizontsl test{
   if(numbers[i][0]>0 && numbers[i][1]>0 && numbers[i][2]>0 ){
   if(numbers[i][0]== 1 && numbers[i][1]==1 && numbers[i][2]==1 ){
    gameover=1;
   ttgo->tft->fillRect(posX[i]+31,9, 6,220,TFT_RED);
   
   }
    if(numbers[i][0]== 2 && numbers[i][1]==2 && numbers[i][2]==2 ){
      gameover=1;
 ttgo->tft->fillRect(posX[i]+31,9, 6,220,TFT_RED);
    }
  }
  }

     for(int i=0;i<3;i++){ ///horizontsl test{
   if(numbers[0][i]>0 && numbers[1][i]>0 && numbers[2][i]>0 ){
   if(numbers[0][i]== 1 && numbers[1][i]==1 && numbers[2][i]==1 ){
    gameover=1;
    
        ttgo->tft->fillRect(9,posX[i]+31, 220,6,TFT_RED);
  
   }
    if(numbers[0][i]== 2 && numbers[1][i]==2 && numbers[2][i]==2 ){
      gameover=1;
    ttgo->tft->fillRect(9,posX[i]+31, 220,6,TFT_RED);
    }
  }
  }

  if(numbers[0][0]>0 && numbers[1][1]>0 && numbers[2][2]>0) //digonal 1
       {
          if(numbers[0][0]==1 && numbers[1][1]==1 && numbers[2][2]==1){
            gameover=1;
      ttgo->tft->drawLine(13,14,219,220,TFT_RED);
        ttgo->tft->drawLine(14,14,220,220,TFT_RED);
        ttgo->tft->drawLine(15,14,221,220,TFT_RED);
          }

             if(numbers[0][0]==2 && numbers[1][1]==2 && numbers[2][2]==2){
        gameover=1;
        ttgo->tft->drawLine(13,14,219,220,TFT_RED);
        ttgo->tft->drawLine(14,14,220,220,TFT_RED);
        ttgo->tft->drawLine(15,14,221,220,TFT_RED);
          }
        }

          if(numbers[0][2]>0 && numbers[1][1]>0 && numbers[2][0]>0) //digonal 2
       {
          if(numbers[0][2]==1 && numbers[1][1]==1 && numbers[2][0]==1){
            gameover=1;
      
        ttgo->tft->drawLine(14,220,220,14,TFT_RED);
        ttgo->tft->drawLine(14,219,220,13,TFT_RED);
        ttgo->tft->drawLine(14,221,220,15,TFT_RED);
        
          }

             if(numbers[0][2]==2 && numbers[1][1]==2 && numbers[2][0]==2){
              gameover=1;
        
     
        ttgo->tft->drawLine(14,220,220,14,TFT_RED);
        ttgo->tft->drawLine(14,219,220,13,TFT_RED);
        ttgo->tft->drawLine(14,221,220,15,TFT_RED);
     
          }
        }
    
    }
