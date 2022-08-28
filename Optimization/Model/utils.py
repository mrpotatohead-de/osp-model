def readfile(res_raw, res_opt):
    raw_file = open(res_raw, 'r')
    opt_file = open(res_opt, 'r')

    num_iter = []
    raw_time = []
    opt_time = []

    for line in raw_file.readlines():
        line = line.split()
        num_iter.append(line[0])
        raw_time.append(line[1])
    
    for line in opt_file.readlines():
        line = line.split()
        opt_time.append(line[1])

    raw_file.close()
    opt_file.close()
    return num_iter, raw_time, opt_time

def md_table(num_iter, raw_time, opt_time):
    table  = '| iteration | time_raw (s) | time_opt (s) | ratio |\n'
    table += '| --------- | ------------ | ------------ | ----- |\n'
    for i, j, k in zip(num_iter, raw_time, opt_time):
        table += f'| {i} | {float(j)} | {float(k)} | {float(j) / float(k):.2f} |\n'
    return table

def plotting(num_iter, raw_time, opt_time):
    import matplotlib.pyplot as plt
    import numpy as np

    x = np.arange(len(num_iter))  # the label locations
    width = 0.35  # the width of the bars

    fig, ax = plt.subplots()
    rects1 = ax.bar(x - width/2, raw_time, width, label='raw')
    rects2 = ax.bar(x + width/2, opt_time, width, label='optimized')

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel('Training Time (sec)')
    ax.set_title('Scores by group and gender')
    ax.set_xticks(x, num_iter)
    ax.set_yticks(x, num_iter)
    ax.legend()

    ax.bar_label(rects1, padding=3)
    ax.bar_label(rects2, padding=3)

    fig.tight_layout()

    # plt.show()
    plt.savefig('log/plot.png')

def main():
    num_iter, raw_time, opt_time = readfile('log/raw.txt', 'log/opt.txt')
    # plotting(num_iter, raw_time, opt_time)
    table = md_table(num_iter, raw_time, opt_time)
    print(table)

if __name__ == '__main__':
    main()