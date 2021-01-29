#include "defs.h"

/*
   Function: updateRunnerDisplay
    Purpose: update runner avatar at current and new position
         in: pointer to RunnerType object
         in: new row position
     return: none
*/
void updateRunnerDisplay(RunnerType *runner, int tempPos){
   int x = 9;
   char hp[MAX_BUF];
   scrPrt(" ", runner->ent.currPos, runner->ent.path);      
   scrPrt(runner->ent.avatar, tempPos, runner->ent.path);
        
   for (int i = 0; i < race->numRunners; i++){
      if (strcmp(runner->name, runnerAt(i)->name) == 0)
         break;
      x += 4;     
   } 
   sprintf(hp,"%2d", runner->health);
   scrPrt("  ", 2,HEALTH_COL + x);
   scrPrt(hp, 2,HEALTH_COL + x);   
}

/*
   Function: *goRunner
    Purpose: a thread function that moving a runner on the race track with randomized step forward/backward
         in: pointer to the RunnerType thread
     return: none
*/
void *goRunner(void *arg){
   
   RunnerType *runner = (RunnerType*) arg;

   int rng, step, dmg;
   int tempPos = runner->ent.currPos;
   char stt[MAX_BUF];
   
   while (runner->ent.currPos != END_POS && runner->dead == C_FALSE){
      // computing runner's next position
      dmg = 3;
      rng = randm(10);
      if (rng < 7){
         step = randm(4) + 1;
         if (runner->health <= step){
            step = runner->health;
         }         
         if ((runner->ent.currPos - step) <= END_POS)
            step = runner->ent.currPos - END_POS;
            
         tempPos = runner->ent.currPos - step;  
         runner->health = runner->health - step; 
      }
      else {
         step = randm(3) + 1;
         if(runner->ent.currPos == START_POS)
            step = 0;  
         else if (runner->ent.currPos + step >= START_POS)
            step = START_POS - runner->ent.currPos; 
         tempPos = runner->ent.currPos + step;         
      }          
      
      // check collision
      
      if (sem_wait(&(race->mutex))){
         printf("semaphore wait error\n");
         exit(1);
      } 
      for (int i = 0; i < race->numDorcs; i++){
         if (race->dorcs[i]->currPos == tempPos && race->dorcs[i]->path == runner->ent.path){
            sprintf(stt,"STATUS:  dorc collides with %s", runner->name);
            if (runner->health <= dmg)
               dmg = runner->health;            
            scrPrt(stt, race->statusRow, HEALTH_COL);
            ++(race->statusRow);   
            runner->health = runner->health - dmg;            
         }     
      }
      if (sem_post(&(race->mutex))){
         printf("semaphore post error\n");
         exit(1);
      }       
     
      // move runner
      if (sem_wait(&(race->mutex))){
         printf("semaphore wait error\n");
         exit(1);
      }    
      updateRunnerDisplay(runner, tempPos);
      if (sem_post(&(race->mutex))){
         printf("semaphore post error\n");
         exit(1);
      } 
  
      runner->ent.currPos = tempPos;
      
      // check runner's health
      if (runner->health == 0){
         runner->dead = C_TRUE;
         strcpy(runner->ent.avatar, "+");   
         scrPrt(runner->ent.avatar, runner->ent.currPos, runner->ent.path);
         if (dmg == 3)
            sprintf(stt,"STATUS:  %s died due to exhaust", runner->name);         
         else
            sprintf(stt,"STATUS:  %s was killed by a dorc", runner->name);                             
         scrPrt(stt, race->statusRow, HEALTH_COL); 
         ++(race->statusRow);
      }            
      usleep(250000);
   }
   
   if (sem_wait(&(race->mutex))){
      printf("semaphore wait error\n");
      exit(1);
   } 
   if (runner->dead == C_FALSE){
      sprintf(stt,"*STATUS: %s cross the finish line", runner->name);
      scrPrt(stt, race->statusRow, HEALTH_COL);
      ++(race->statusRow);
      if (strlen(race->winner) == 0)
         strcpy(race->winner, runner->name);    
   }
   if (sem_post(&(race->mutex))){
      printf("semaphore post error\n");
      exit(1);
   }    
   return 0;
}
