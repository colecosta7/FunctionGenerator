/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Function Generator
  ******************************************************************************
  *Program interfaces DAC, Board, and keypad to display waveforms
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "KEYPAD_lib/keypad_lib.h"
#include "DAC_lib/DAC_lib.h"
#include "waveforms.h"

void SystemClock_Config(void);

//points holds the points to be plotted on waveform
static int32_t* points;
//current index into array
int16_t idx;
//size of the array
int16_t size;

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  //configure keypad
  keypad_config();

  //initialize DAC
  DAC_init();

  //initial wave to display
  int16_t freq = 100;
  int8_t wave = SQUARE;
  int16_t duty;

  //index into points array
  idx = 0;

  //size of the points array (per period)
  size = SAMPLES_SEC / freq;

  //set to 50% duty cycle
  duty = size / 2;

  //set array to hold values of 100 HZ square wave
  points = waveform(freq, wave, duty);

  //initialize TIM2
  RCC->APB1ENR1 |= (RCC_APB1ENR1_TIM2EN);			//initialize RCC
  TIM2->DIER |= (TIM_DIER_UIE);						// enable interrupt on update event
  TIM2->SR &= ~(TIM_SR_UIF);						// clear update interrupt flag
  TIM2->ARR = CLOCKFREQ/SAMPLES_SEC + 5;			//set ARR to Output rate
  TIM2->CR1 |= (TIM_CR1_CEN);						//start the timer

  // enable interrupts in NVIC
  NVIC->ISER[0] = (1 << (TIM2_IRQn & 0x1F));

  __enable_irq();	// enable interrupts globally

  //create state type variable
  typedef enum{
	  WAIT,
	  CHANGE_DUTY,
	  CHANGE_FREQ,
	  CHANGE_WAVE
  }state_type;

  //initial state
  state_type state = WAIT;

  //holds current key press
  int8_t key;

  while (1)
  {
	//FSM
    switch(state){
    	//state to wait for key press
    	case WAIT:
    		//get a key
    		key = keypad_getKey();
    		//software delay for keypad
    		for(int32_t i = 0; i<200000; i++);

    		//if a key was pressed
    		if (key != -1){
    			//if the key was 1,2,3,4,5 change frequency
    			if(key > 0 && key <= 5){
    				state = CHANGE_FREQ;
    			}

    			//change state to wave
    			else if(key > 5 && key <= 9){
    				wave = key;
    				state = CHANGE_WAVE;
    			}

    			//change state to duty
    			else if((key == 0) || (key == 14) || (key == 15)){
    				//only change duty if it is a square wave
    				if(wave == SQUARE)
    					state = CHANGE_DUTY;
    			}

    		}

    		//else stay in wait state
    		else {
    			state = WAIT;
    		}

    		break;

    	//state to change duty cycle of square wave
    	case CHANGE_DUTY:
    		//key 0  resets 50% duty cycle
    		if(key == 0){
    			duty = size / 2;
    			state = CHANGE_WAVE;
    		}

    		//key * decreases duty cycle by 10%
    		else if(key == 14){
    			//do not increase if it is at minimum of 10%
    			int16_t decr = size / 10;
    			if((duty + decr) <= (size - decr)){
    				//decrease duty cycle by 10%
    				duty += size / 10;
    				state = CHANGE_WAVE;
    			}

    			//if at minimum go back to wait
    			else
    				state = WAIT;
    		}

    		//key # increases duty cycle by 10%
    		else if(key == 15){
    			//do not increase if it is at maximum of 90%
    			int16_t incr = size / 10;
    			if((duty - incr) >= (size - (size * 9 / 10))){
    				//increase duty cycle by 10%
    				duty -= size / 10;
    				state = CHANGE_WAVE;
    			}
    			//if at maximum go back to wait
    			else
    				state = WAIT;
    		}

    		//default
    		else
    			state = WAIT;

    		break;

    	//state to change the frequency
    	case CHANGE_FREQ:
    		//keys are 1,2,3,4,5 representing each frequency
    		freq = 100 * key;
    		//update the size of the table
    		size = SAMPLES_SEC / freq;
    		//update the new 50% duty cycle if it is a square
    		if(wave == SQUARE)
    			duty = size / 2;

    		state = CHANGE_WAVE;
    		break;

    	case CHANGE_WAVE:
    		//reset the index
    		idx = 0;
    		//generate a new table of points for every wave change
    		points = waveform(freq, wave, duty);

    		state = WAIT;
    		break;

    	default:
    		state = WAIT;

    }//end switch

  }//end while

}//end main

//Timer 2 ISR: plot a new point every time the timer goes off
void TIM2_IRQHandler(void){
	//check status register for universal event flag
	if(TIM2->SR & TIM_SR_UIF){					//if the interrupt occurs
		TIM2->SR &= ~(TIM_SR_UIF);				//clear interrupt flag
		if(idx == size){						//if the end of table is reached
			idx = 0;							//reset the index
		}
		DAC_write(*(points + idx));				//write a point to the DAC
		idx++;									//increment index into lookup table
	}
}//end TIM2ISR


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_10;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
