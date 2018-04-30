using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Threading;

namespace BreastCancer
{
    class ExperimentSetup
    {
        public List<BreastCancerCase> CaseBase { get; set; }
        public List<BreastCancerCase> TestSet { get; set; }
        public List<float> MeanWeights { get; set; }
        public List<float> ErrorWeights { get; set; }
        public List<float> ExtremeWeights { get; set; }
        public double TestRatio { get; set; }


        // Creates a new randomized experiment setup, splitting the data in two parts
        public ExperimentSetup(List<BreastCancerCase> dataset, double testRatio)
        {
            int testCount = (int) Math.Round(dataset.Count * testRatio);

            Random rng = new Random();
            int n = dataset.Count;
            while (n > 1) {
                n--;
                int k = rng.Next(n + 1);
                BreastCancerCase value = dataset[k];
                dataset[k] = dataset[n];
                dataset[n] = value;
            }

            CaseBase = dataset.GetRange(0, dataset.Count - testCount);
            TestSet = dataset.GetRange(dataset.Count - testCount, testCount);
            TestRatio = testRatio;
        }
    }

    class Program
    {
		static List<BreastCancerCase> Parse(List<List<string>> input)
		{
			return input.Select(row => new BreastCancerCase(row)).ToList();
		}

        static double RunExperiment(ExperimentSetup setup, bool print = false)
        {
            int n = setup.TestSet.Count;
            int[,] confusionMatrix = new int[n, n]; // Implicitly filled with zeros

            foreach (BreastCancerCase testCase in setup.TestSet)
            {
                List<BreastCancerCase> ordered = setup.CaseBase
                    .OrderByDescending(value => value.CompareTo(
                        testCase, setup.MeanWeights, setup.ErrorWeights, setup.ExtremeWeights
                    )).ToList();

                if (print)
                {
                    Console.WriteLine("Case under evaluation: ");
                    testCase.Print();
                    Console.WriteLine("\nMost similar cases in the database:\n");
                }

                bool actual = testCase.Malignant;
                bool predicted = ordered[0].Malignant;

                int row = predicted ? 0 : 1;
                int column = actual ? 0 : 1;
                confusionMatrix[row, column]++;

                if (print)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        BreastCancerCase match = ordered[i];

                        double y = match.CompareTo(testCase, setup.MeanWeights, setup.ErrorWeights, setup.ExtremeWeights);

                        Console.WriteLine("Match n. #" + i);
                        match.Print();

                        bool valid = match.Malignant == actual;

                        Console.WriteLine("\nSimilarity: " + y);
                        Console.WriteLine("Valid diagnosis: " + (valid ? "YES" : "NO"));
                        Console.WriteLine();
                    }
                }
            }

            // True Negatives + True Positives / Negatives + Positives
            double accuracy = (double) (confusionMatrix[0, 0] + confusionMatrix[1, 1]) / (double) n;

            if (print)
            {
                Console.WriteLine("Outcome:");
                Console.WriteLine("\tB\tM");
                Console.WriteLine("B\t" + confusionMatrix[0, 0] + "\t" + confusionMatrix[0, 1]);
                Console.WriteLine("M\t" + confusionMatrix[1, 0] + "\t" + confusionMatrix[1, 1]);
                Console.WriteLine("Accuracy: " + accuracy);
            }

            return accuracy;
        }

        static IEnumerable<List<float>> f(List<float> vals, int n, List<float> options)
        {
            foreach (float v in options)
            {
                List<float> copy = new List<float>(vals);
                copy.Add(v);
                if (n > 1) {
                    foreach (List<float> z in f(copy, n - 1, options))
                    {
                        yield return z;
                    }
                } else {
                    yield return copy;
                }
            }
        }

        static IEnumerable<List<float>> GenerateWeights(int n, List<float> options) {
            foreach (List<float> z in f(new List<float>(), n, options))
            {
                yield return z;
            }
        }

        static void ReplicateUntil(List<float> values, int targetCount) {
            int n = values.Count;
            while (values.Count < targetCount) {
                values.AddRange(values.GetRange(0, n));
            }
        }

        static void GenerateAndExecuteExperiments(List<BreastCancerCase> data)
        {
            int nChoices = 2;

            List<float> weightOptions = Enumerable.Range(1, nChoices)
                .Select(x => (float) x / nChoices)
                .ToList();

            List<double> ratioChoices = new List<double>() {0.2, 0.3};
            int k = TumourFeatures.FeatureCount;

            using (var writer = new StreamWriter("./experiments.csv"))
            {
                Enumerable.Range(1, k * 3).ToList()
                    .ForEach(x => writer.Write("w" + x + ","));

                writer.WriteLine("ratio,acc");

                foreach (double ratio in ratioChoices) {
                    var generator = GenerateWeights(k, weightOptions);

                    int replications = 5;
                    int combinations = (int) Math.Pow(weightOptions.Count, k) * replications;
                    int current = 0;

                    foreach (List<float> weights in generator)
                    {
                        ReplicateUntil(weights, k * 3);
                    
                        //List<double> values = new List<double>();

                        for (int i = 0; i < replications; i++) {
                            ExperimentSetup setup = new ExperimentSetup(data, ratio);
                            setup.MeanWeights = weights.GetRange(0, k);
                            setup.ErrorWeights = weights.GetRange(k, k);
                            setup.ExtremeWeights = weights.GetRange(k * 2, k);

                            double accuracy = RunExperiment(setup, true);

                            weights.ForEach(x => writer.Write(x + ","));
                            writer.WriteLine(ratio + "," + accuracy);

                            Console.WriteLine((current++) + "/" + combinations + " => " + accuracy);
                        }
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            Thread.CurrentThread.CurrentCulture = CultureInfo.InvariantCulture;

            List<BreastCancerCase> data = Parse(Reader.Read("./data.csv", ','));

            GenerateAndExecuteExperiments(data);
        }
    }
}
