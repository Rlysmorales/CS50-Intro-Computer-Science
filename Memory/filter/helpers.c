#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //looping over the height and width basically the picture is a square
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //in order to get grey you gave to add all the pixel and get the average. Since grey is between
            //Black that is 0 and white which is 255. 
            int greycolor = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            //Making sure every color is in the middle or the average
            image[i][j].rgbtBlue = greycolor;
            image[i][j].rgbtGreen = greycolor;
            image[i][j].rgbtRed = greycolor;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{   
      // again looping over the entire picture
      for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   
            //Sepias has an algorithm to get each color correct pixel
            int sepiared = round(((image[i][j].rgbtRed * .393) + (image[i][j].rgbtGreen * .796) + (image[i][j].rgbtBlue * .189)) / 3.0);
            int sepiagreen = round(((image[i][j].rgbtRed * .349) + (image[i][j].rgbtGreen * .686) + (image[i][j].rgbtBlue * .168)) / 3.0);
            int sepiablue = round(((image[i][j].rgbtRed * .272) + (image[i][j].rgbtGreen * .534) + (image[i][j].rgbtBlue * .131)) / 3.0);

            // In the case that the formula ends color is below 0 or above 255.
            // Just automatically set it to 255
            if(sepiared < 0 || sepiared > 255){
                sepiared = 255;
            }

            if(sepiagreen < 0 || sepiagreen > 255){
                sepiagreen = 255;
            }
            if(sepiablue < 0 || sepiablue > 255){
                sepiablue = 255;
            }

            //Implement the formula total to each color
            image[i][j].rgbtBlue = sepiablue;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtRed = sepiared;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
     for (int i = 0; i < height; i++)
    {   
        //This will stop the loop at the half way mark
        //If not it will swap again the pixel to the original position
        for (int j = 0; j < width / 2; j++)
        {
            //Swaping begings by creating a temporary variable
            //Where we will place the 1st pixel
            RGBTRIPLE temporary = image[i][j];
            //This is the formula to swap and move the last pixel in the 1st position
            image[i][j] = image[i][width - (j + 1)];
            //placing the value in temporary variable
            image[i][width - (j + 1)] = temporary;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temporary[height][width];
    float count = 0;
    int redSum = 0;
    int greenSum = 0;
    int blueSum = 0;

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            temporary[i][j] = image[i][j];

            //Doing a loop to find the neighbouring pixel
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    //Find the coordinates of the pixel you are in
                    int xequals = i + x;
                    int yequals = j + y;

                    //Check if we have invalid pixels. 
                    if (xequals < (height -1) || yequals < (width - 1) || xequals >= 0 || yequals >= 0)
                    {

                        continue;
                    }
                    //Add the neighbouring pixel
                    redSum += image[xequals][yequals].rgbtRed;
                    greenSum += image[xequals][yequals].rgbtGreen;
                    blueSum += image[xequals][yequals].rgbtBlue;
                    //count total # of valid neighbouring pixel 
                    count++;
                }
                //get the total of the neighbouring pixel
                redSum = round(redSum / count);
                greenSum = round(greenSum / count);
                blueSum = round(blueSum / count);
                
                temporary[i][j].rgbtRed = redSum;
                temporary[i][j].rgbtGreen = greenSum;
                temporary[i][j].rgbtBlue = blueSum;

            }

        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   
            //apply the changes to the picture depending on the color
            image[i][j].rgbtRed = temporary[i][j].rgbtRed;
            image[i][j].rgbtGreen = temporary[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temporary[i][j].rgbtBlue;
        }
    }

    return;
}

