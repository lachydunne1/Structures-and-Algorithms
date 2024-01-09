from scipy import stats as ss
import sys
import argparse
import csv
import numpy as np


def generate_rv(distribution, size=1000):
    if distribution == 'gaussian':
        mean, std_dev = 0, 1  # Standard Gaussian parameters
        return ss.norm.rvs(mean, std_dev, size=size)
    
    elif distribution == 'uniform':
        lower, upper = 0, 1  # Standard Uniform parameters
        return ss.uniform.rvs(lower, upper, size=size)
    
    elif distribution == 'exponential':
        lambda_inv = 1  # Rate parameter (inverse of lambda)
        return ss.expon.rvs(scale=lambda_inv, size=size)
    
    elif distribution == 'poisson':
        lambda_ = 5  # Rate of occurrence (lambda)
        return ss.poisson.rvs(mu=lambda_, size=size)
    
    elif distribution == 'binomial':
        n, p = 10, 0.5  # Number of trials and success probability
        return ss.binomial.rvs(n, p, size=size)
        
    # Add other distributions here as needed
    else:
        raise ValueError(f"Unsupported distribution type: {distribution}")

def save_to_csv(data, filename):
    with open(filename, 'w', newline='') as file:
        writer = csv.writer(file)
        for value in data:
            writer.writerow([value])



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Generate random variable distributions.')

    parser.add_argument('--new', help='Generate new data distribution')
    parser.add_argument('--dist', choices=['gaussian', 'uniform', 'exponential', 'poisson', 'binomial'], help='Type of distribution to generate')
    parser.add_argument('--size', type=int, default=1000, help='Number of samples to generate')
    parser.add_argument('--output', default='output.csv', help='Output CSV file')

    args = parser.parse_args()

    if args.new:
        try:
            rv_data = generate_rv(args.dist, size=args.size)
            save_to_csv(rv_data, args.output)
            print(f"Data generated and saved to {args.output}")
        except ValueError as e:
            print(e)
            sys.exit(1)


