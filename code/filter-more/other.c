sum3 = round((float)(image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue)/3);