using System;
using System.Collections.Generic;

namespace BreastCancer
{
  class TumourFeatures
    {
        public static int FeatureCount = 10;

        public float Radius { get; set; }
        public float Texture { get; set; }
        public float Perimeter { get; set; }
        public float Area { get; set; }
        public float Smoothness { get; set; }
        public float Compactness { get; set; }
        public float Concavity { get; set; }
        public float ConcavePoints { get; set; }
        public float Symmetry { get; set; }
        public float FractalDimension { get; set; }

        public TumourFeatures(float radius, float texture, float perimeter, float area, float smoothness,
            float compactness, float concavity, float concavePoints, float symmetry, float fractalDimension)
        {
            Radius = radius;
            Texture = texture;
            Perimeter = perimeter;
            Area = area;
            Smoothness = smoothness;
            Compactness = compactness;
            Concavity = concavity;
            ConcavePoints = concavePoints;
            Symmetry = symmetry;
            FractalDimension = fractalDimension;
        }

        public TumourFeatures(List<float> values)
        : this(values[0], values[1], values[2], values[3], values[4],
            values[5],values[6], values[7], values[8], values[9])
        {

        }

        public void Print()
        {
            Console.WriteLine("Radius: " + Radius);
            Console.WriteLine("Texture: " + Texture);
            Console.WriteLine("Perimeter: " + Perimeter);
            Console.WriteLine("Area: " + Area);
            Console.WriteLine("Smoothness: " + Smoothness);
            Console.WriteLine("Compactness: " + Compactness);
            Console.WriteLine("Concavity: " + Concavity);
            Console.WriteLine("Concave Points: " + ConcavePoints);
            Console.WriteLine("Symmetry: " + Symmetry);
            Console.WriteLine("Fractal Dimension: " + FractalDimension);
        }

        public double CalculateSimilarity(TumourFeatures other, List<float> weights)
        {
            float maxRadius = 30;
            float maxTexture = 31; 
            float maxPerimeter = 200;
            float maxArea = 2500;
            float maxConcavity = 140;
            float maxConcavePoints = 340;
            float maxSymmetry = 400;
            float maxFractalDimension = 250;
            
            float minRadius = 1;
            float minTexture = 1;
            float minPerimeter = 1;
            float minArea = 100;
            float minConcavity = 1;
            float minConcavePoints = 10;
            float minSymmetry = 0;
            float minFractalDimension = 0;

            List<float> similarities = new List<float>() {
                1 - (Math.Abs(other.Radius - this.Radius) / maxRadius - minRadius),
                1 - (Math.Abs(other.Texture - this.Texture) / maxTexture - minTexture),
                1 - (Math.Abs(other.Perimeter - this.Perimeter) / maxPerimeter - minPerimeter),
                1 - (Math.Abs(other.Area - this.Area) / maxArea - minArea),
                1 - (Math.Abs(other.Concavity - this.Concavity) / maxConcavity - minConcavity),
                1 - (Math.Abs(other.ConcavePoints - this.ConcavePoints) / maxConcavePoints - minConcavePoints),
                1 - (Math.Abs(other.Symmetry - this.Symmetry) / maxSymmetry - minSymmetry),
                1 - (Math.Abs(other.FractalDimension - this.FractalDimension) / maxFractalDimension - minFractalDimension)
            };

           
            
            float similarityTotal = 0;
            float weightSum = 0;

            for (int index = 0; index < similarities.Count; index++) {
                similarityTotal += weights[index] * similarities[index];
                weightSum += weights[index];
            }
            
            similarityTotal = similarityTotal / weightSum;
            
            return similarityTotal;
        }
    }
}
