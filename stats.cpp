/**
 *  @file stats.cpp
 *  @description implementation of a stats class for rapid calculation of color averages
 *   and total color differences in CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN
 */

#include "stats.h"

 /**
  *  Computes/retrieves the sum of a single color channel in a defined rectangular region
  *  @pre channel is a valid channel identifier
  *  @pre upper, left, lower, and right are valid image coordinates
  *  @param channel - one of 'r', 'g', or 'b'
  *  @param upper - y-coordinate of the upper edge of the rectangular region
  *  @param left - x-coordinate of the left side of the rectangular region
  *  @param lower - y-coordinate of the lower edge of the rectangular region
  *  @param right - x-coordinate of the right side of the rectangular region
  *  @return the sum of the appropriate color channel values in the defined rectangular area
  */
unsigned long Stats::GetColorSum(char channel, unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  unsigned sum = 0;
  if (channel == 'r') {
    if (upper == 0 && left == 0) {
      sum = sumR[right][lower];
    } else if (upper == 0) {
      sum = sumR[right][lower] - sumR[left-1][lower];
    } else if (left == 0) {
      sum = sumR[right][lower] - sumR[right][upper-1];
    } else {
      sum = sumR[right][lower] - sumR[left-1][lower] - sumR[right][upper-1] + sumR[left-1][upper-1];
    }
  } else if (channel == 'g') {
    if (upper == 0 && left == 0) {
      sum = sumG[right][lower];
    } else if (upper == 0) {
      sum = sumG[right][lower] - sumG[left-1][lower];
    } else if (left == 0) {
      sum = sumG[right][lower] - sumG[right][upper-1];
    } else {
      sum = sumG[right][lower] - sumG[left-1][lower] - sumG[right][upper-1] + sumG[left-1][upper-1];
    }
  } else {
    if (upper == 0 && left == 0) {
      sum = sumB[right][lower];
    } else if (upper == 0) {
      sum = sumB[right][lower] - sumB[left-1][lower];
    } else if (left == 0) {
      sum = sumB[right][lower] - sumB[right][upper-1];
    } else {
      sum = sumB[right][lower] - sumB[left-1][lower] - sumB[right][upper-1] + sumB[left-1][upper-1];
    }
  }
  return sum; // REPLACE THIS STUB
}

/**
 *  Computes/retrieves the sum of alpha values in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the sum of the alpha values in the defined rectangular area
 */
double Stats::GetAlphaSum(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  double sum = 0;
  if (upper == 0 && left == 0) {
      sum = sumA[right][lower];
    } else if (upper == 0) {
      sum = sumA[right][lower] - sumA[left-1][lower];
    } else if (left == 0) {
      sum = sumA[right][lower] - sumA[right][upper-1];
    } else {
      sum = sumA[right][lower] - sumA[left-1][lower] - sumA[right][upper-1] + sumA[left-1][upper-1];
    }
  return sum; // REPLACE THIS STUB
}

/**
 *  Computes/retrieves the squared sum of a single color channel in a defined rectangular region
 *  @pre channel is a valid channel identifier
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param channel - one of 'r', 'g', or 'b'
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the squared sum of the appropriate color channel values in the defined rectangular area
 */
unsigned long Stats::GetColorSumSq(char channel, unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  unsigned sum = 0;
  if (channel == 'r') {
    if (upper == 0 && left == 0) {
      sum = sumSqR[right][lower];
    } else if (upper == 0) {
      sum = sumSqR[right][lower] - sumSqR[left-1][lower];
    } else if (left == 0) {
      sum = sumSqR[right][lower] - sumSqR[right][upper-1];
    } else {
      sum = sumSqR[right][lower] - sumSqR[left-1][lower] - sumSqR[right][upper-1] + sumSqR[left-1][upper-1];
    }
  } else if (channel == 'g') {
    if (upper == 0 && left == 0) {
      sum = sumSqG[right][lower];
    } else if (upper == 0) {
      sum = sumSqG[right][lower] - sumSqG[left-1][lower];
    } else if (left == 0) {
      sum = sumSqG[right][lower] - sumSqG[right][upper-1];
    } else {
      sum = sumSqG[right][lower] - sumSqG[left-1][lower] - sumSqG[right][upper-1] + sumSqG[left-1][upper-1];
    }
  } else {
    if (upper == 0 && left == 0) {
      sum = sumSqB[right][lower];
    } else if (upper == 0) {
      sum = sumSqB[right][lower] - sumSqB[left-1][lower];
    } else if (left == 0) {
      sum = sumSqB[right][lower] - sumSqB[right][upper-1];
    } else {
      sum = sumSqB[right][lower] - sumSqB[left-1][lower] - sumSqB[right][upper-1] + sumSqB[left-1][upper-1];
    }
  }
  return sum; // REPLACE THIS STUB
}

/**
 *  Computes/retrieves the squared sum of alpha values in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the squared sum of the alpha values in the defined rectangular area
 */
double Stats::GetAlphaSumSq(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  double sum = 0;
    if (upper == 0 && left == 0) {
      sum = sumSqA[right][lower];
    } else if (upper == 0) {
      sum = sumSqA[right][lower] - sumSqA[left-1][lower];
    } else if (left == 0) {
      sum = sumSqA[right][lower] - sumSqA[right][upper-1];
    } else {
      sum = sumSqA[right][lower] - sumSqA[left-1][lower] - sumSqA[right][upper-1] + sumSqA[left-1][upper-1];
    }
  return sum; // REPLACE THIS STUB
}

/**
 *  Simple function to compute the number of pixels in a defined rectangular region
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return the area of the defined rectangular area, in pixels
 */
unsigned int Stats::GetRectangleArea(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  unsigned area = 0; 
  area = (lower - upper + 1) * (right - left + 1);
  return area; // REPLACE THIS STUB
}

/**
 *  Parameterized constructor
 *  Builds the channel sum and squared sum vectors from the supplied input image.
 *  Each channel sum vector's entry (x,y) will contain the sum of their respective
 *  color channels of all pixels in the rectangular image region bounded by (0,0) and (x,y).
 *  Likewise, each channel squared sum vector's entry (x,y) will contain the squared sum of their
 *  respective color channels of all pixels in the rectangular image region bounded by (0,0) and (x,y).
 *
 *  ***DON'T FORGET TO PRE-MULTIPLY THE ALPHA CHANNEL***
 * 
 *  @param img - input image from which the channel sum vectors will be populated
 */
Stats::Stats(const PNG& img) {
  // complete your implementation below
  sumA.resize(img.width());
  sumR.resize(img.width());
  sumG.resize(img.width());
  sumB.resize(img.width());

  sumSqA.resize(img.width());
  sumSqR.resize(img.width());
  sumSqG.resize(img.width());
  sumSqB.resize(img.width());
  
  RGBAPixel* curr;
  for (unsigned i = 0; i < img.width(); i++) {
      sumA[i].resize(img.height());
      sumR[i].resize(img.height());
      sumG[i].resize(img.height());
      sumB[i].resize(img.height());

      sumSqA[i].resize(img.height());
      sumSqR[i].resize(img.height());
      sumSqG[i].resize(img.height());
      sumSqB[i].resize(img.height());
    for (unsigned j = 0; j < img.height(); j++) {
      curr = img.getPixel(i, j);

      if (i == 0 && j == 0) {
        sumA[i][j] = (curr->a) * 255.0;
        sumR[i][j] = curr->r;
        sumG[i][j] = curr->g;
        sumB[i][j] = curr->b;

        sumSqA[i][j] = ((curr->a) * 255.0) * ((curr->a) * 255.0);
        sumSqR[i][j] = (curr->r) * (curr->r);
        sumSqG[i][j] = (curr->g) * (curr->g);
        sumSqB[i][j] = (curr->b) * (curr->b);

      } else if (i == 0) {
        sumA[i][j] = sumA[i][j-1] + ((curr->a) * 255.0);
        sumR[i][j] = sumR[i][j-1] + curr->r;
        sumG[i][j] = sumG[i][j-1] + curr->g;
        sumB[i][j] = sumB[i][j-1] + curr->b;

        sumSqA[i][j] = sumSqA[i][j-1] + (((curr->a) * 255.0) * ((curr->a) * 255.0));
        sumSqR[i][j] = sumSqR[i][j-1] + ((curr->r) * (curr->r));
        sumSqG[i][j] = sumSqG[i][j-1] + ((curr->g) * (curr->g));
        sumSqB[i][j] = sumSqB[i][j-1] + ((curr->b) * (curr->b));

      } else if (j == 0) {
        sumA[i][j] = sumA[i-1][j] + ((curr->a) * 255.0);
        sumR[i][j] = sumR[i-1][j] + curr->r;
        sumG[i][j] = sumG[i-1][j] + curr->g;
        sumB[i][j] = sumB[i-1][j] + curr->b;

        sumSqA[i][j] = sumSqA[i-1][j] + (((curr->a) * 255.0) * ((curr->a) * 255.0));
        sumSqR[i][j] = sumSqR[i-1][j] + ((curr->r) * (curr->r));
        sumSqG[i][j] = sumSqG[i-1][j] + ((curr->g) * (curr->g));
        sumSqB[i][j] = sumSqB[i-1][j] + ((curr->b) * (curr->b));

      } else {
        sumA[i][j] = sumA[i-1][j] + sumA[i][j-1] - sumA[i-1][j-1] + ((curr->a) * 255.0);
        sumR[i][j] = sumR[i-1][j] + sumR[i][j-1] - sumR[i-1][j-1] + curr->r;
        sumG[i][j] = sumG[i-1][j] + sumG[i][j-1] - sumG[i-1][j-1] + curr->g;
        sumB[i][j] = sumB[i-1][j] + sumB[i][j-1] - sumB[i-1][j-1] + curr->b;

        sumSqA[i][j] = sumSqA[i-1][j] + sumSqA[i][j-1] - sumSqA[i-1][j-1] + (((curr->a) * 255.0) * ((curr->a) * 255.0));
        sumSqR[i][j] = sumSqR[i-1][j] + sumSqR[i][j-1] - sumSqR[i-1][j-1] + ((curr->r) * (curr->r));
        sumSqG[i][j] = sumSqG[i-1][j] + sumSqG[i][j-1] - sumSqG[i-1][j-1] + ((curr->g) * (curr->g));
        sumSqB[i][j] = sumSqB[i-1][j] + sumSqB[i][j-1] - sumSqB[i-1][j-1] + ((curr->b) * (curr->b));
      }
    }
  }
  

}

/**
 *  Computes/retrieves the average color of all pixels contained in the rectangle
 *  bounded by upper, left, lower, and right. Fractional values should be
 *  truncated/rounded down for assignment into integer variables.
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return pixel containing the average color of the pixels in the defined rectangle
 */
RGBAPixel Stats::GetAvg(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  double a;

  r = GetColorSum('r', upper, left, lower, right) / GetRectangleArea(upper, left, lower, right);
  g = GetColorSum('g', upper, left, lower, right) / GetRectangleArea(upper, left, lower, right);
  b = GetColorSum('b', upper, left, lower, right) / GetRectangleArea(upper, left, lower, right);
  a = GetAlphaSum(upper, left, lower, right) / (GetRectangleArea(upper, left, lower, right) * 255.0);
  return RGBAPixel(r, g, b, a); // REPLACE THIS STUB
}

/**
 *  Computes the total sum squared difference from the mean, for the specified rectangle.
 *  Each channel's sum squared difference is computed separately, and then added to form the total.
 *
 *  Note that using the GetAvg function in computing the sum squared difference will result in
 *  accumulation of error especially with larger rectangles.
 *  You should use more precise computation of the average color for this function's intermediate steps.
 * 
 *  @pre upper, left, lower, and right are valid image coordinates
 *  @param upper - y-coordinate of the upper edge of the rectangular region
 *  @param left - x-coordinate of the left side of the rectangular region
 *  @param lower - y-coordinate of the lower edge of the rectangular region
 *  @param right - x-coordinate of the right side of the rectangular region
 *  @return total sum of squared deviations from the mean, over all color channels.
 */
double Stats::GetSumSqDev(unsigned int upper, unsigned int left, unsigned int lower, unsigned int right) {
  double sum = 0.0;
  double rsqsum = (double) GetColorSumSq('r', upper, left, lower, right);
  double gsqsum = (double) GetColorSumSq('g', upper, left, lower, right);
  double bsqsum = (double) GetColorSumSq('b', upper, left, lower, right);
  double asqsum = GetAlphaSumSq(upper, left, lower, right);

  double rsumsq = (double) GetColorSum('r', upper, left, lower, right);
  double gsumsq = (double) GetColorSum('g', upper, left, lower, right);
  double bsumsq = (double) GetColorSum('b', upper, left, lower, right);
  double asumsq = (double) GetAlphaSum(upper, left, lower, right);

  double area = (double) GetRectangleArea(upper, left, lower, right);

  double rsqd = rsqsum - ((rsumsq * rsumsq) / area);
  double gsqd = gsqsum - ((gsumsq * gsumsq) / area);
  double bsqd = bsqsum - ((bsumsq * bsumsq) / area);
  double asqd = asqsum - ((asumsq * asumsq) / area);
  sum = rsqd + gsqd + bsqd + asqd;
  return sum; // REPLACE THIS STUB
}