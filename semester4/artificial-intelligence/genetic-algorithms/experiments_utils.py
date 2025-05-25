import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

def display_results_table(results):
    table_data = []
    
    for func_name, func_results in results.items():
        for exp_name, metrics in func_results.items():
            representation = exp_name.split('_')[0]
            crossover = '_'.join(exp_name.split('_')[1:])
            
            table_data.append({
                'Function': func_name,
                'Representation': representation.capitalize(),
                'Crossover': crossover.replace('_', ' ').title(),
                'Mean Value': f"{metrics['mean']:.6f}",
                'Std Deviation': f"{metrics['std']:.6f}",
                'Best Value': f"{metrics['best']:.6f}",
                'Global minimum:': f"{metrics['global_optimum']:.6f}",
                'Error:': f"{metrics['distance_to_optimum']:.6f}"
            })
    
    df = pd.DataFrame(table_data)
    print(df.to_string(index=False, col_space=15))
    
    return df

def plot_error_comparison(results):
    plt.style.use('seaborn-v0_8')
    fig, ax = plt.subplots(1, 1, figsize=(12, 8))
    
    functions = list(results.keys())
    experiments = list(results[functions[0]].keys())
    
    exp_labels = []
    for exp in experiments:
        parts = exp.split('_')
        representation = parts[0]
        crossover = '_'.join(parts[1:])
        exp_labels.append(f"{representation.capitalize()}\n{crossover.replace('_', ' ').title()}")
    
    x = np.arange(len(exp_labels))
    width = 0.35
    colors = ['#2E86AB', '#A23B72', '#F18F01', '#C73E1D']
    
    for i, func in enumerate(functions):
        errors = [abs(results[func][exp]['distance_to_optimum']) for exp in experiments]
        bars = ax.bar(x + i*width, errors, width, label=func, 
                     alpha=0.8, color=colors[i % len(colors)])
        
        for bar in bars:
            height = bar.get_height()
            if height > 0:
                ax.text(bar.get_x() + bar.get_width()/2., height,
                        f'{height:.4f}', ha='center', va='bottom', 
                        fontsize=9, rotation=90)
    
    ax.set_xlabel('Method (Representation + Crossover)', fontsize=12)
    ax.set_ylabel('Absolute Error from Global Minimum', fontsize=12)
    ax.set_title('GA Performance: Error from Global Optimum (Log Scale)', fontsize=14, fontweight='bold')
    ax.set_xticks(x + width * (len(functions)-1) / 2)
    ax.set_xticklabels(exp_labels, rotation=45, ha='right')
    ax.set_yscale('log')
    ax.legend()
    ax.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.show()

def create_summary_report(results):
    for func_name, func_results in results.items():
        print(f"\n{func_name.upper()}:")
        
        best_config = max(func_results.items(), key=lambda x: x[1]['mean'])
        worst_config = min(func_results.items(), key=lambda x: x[1]['mean'])
        most_stable = min(func_results.items(), key=lambda x: x[1]['std'])
        
        print(f"Best Mean Performance: {best_config[0]}")
        print(f"  Mean: {best_config[1]['mean']:.6f}, Std: {best_config[1]['std']:.6f}")
        
        print(f"Worst Mean Performance: {worst_config[0]}")
        print(f"  Mean: {worst_config[1]['mean']:.6f}, Std: {worst_config[1]['std']:.6f}")
        
        print(f"Most Stable (Lowest Std): {most_stable[0]}")
        print(f"  Mean: {most_stable[1]['mean']:.6f}, Std: {most_stable[1]['std']:.6f}")
        
        improvement = ((best_config[1]['mean'] - worst_config[1]['mean']) / 
                      abs(worst_config[1]['mean']) * 100)
        print(f"Performance Improvement: {improvement:.2f}%")

def visualize_all_results(results):
    df = display_results_table(results)
    
    plot_error_comparison(results)
    
    create_summary_report(results)
    
    return df