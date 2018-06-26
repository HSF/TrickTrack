import matplotlib.pyplot as plt
import scipy.stats
import numpy as np
import sys

dat = np.loadtxt("profiling_cm_with_reserve.dat")
plt.semilogy(dat[:,0], 10**6 * dat[:,1], 'o', alpha=0.35, color="magenta", mec="black") #, label=r"Max. Matrix dimension $32 \times 32$")
plt.xlabel("Num. found triplets")
plt.ylabel(r"ChainMaker CPU time [$\mu$s]")
#plt.title("  ChainMaker CPU Performance - Triplets")
plt.legend(loc="best")
plt.xscale("log")
plt.savefig("tricktrack_cm_cpu_with_reserve.png")
plt.figure("profiling_cm_binned")
x = dat[:,0]
y = 10**6 * dat[:,1]
means_result = scipy.stats.binned_statistic(x, [y, y**2], 
    bins=np.logspace(0,7,40), 
    statistic='mean')
count_result = scipy.stats.binned_statistic(x, [y, y**2], 
    bins=np.logspace(0,7,40), 
    statistic='mean')
means, means2 = means_result.statistic
counts, counts2 = count_result.statistic
standard_deviations = np.sqrt(means2 - means**2)
standard_deviations = np.sqrt(counts) / counts * means
bin_edges = means_result.bin_edges
bin_centers = (bin_edges[:-1] + bin_edges[1:])/2.
bin_width =  0.5*(bin_edges[1:] - bin_edges[0:-1])
means = np.array(means)

  # do the plot
(_, caps, _) = plt.errorbar(x=bin_centers, y=means, 
      xerr=bin_width, yerr=standard_deviations, 
      linestyle = '', marker='o',capsize=2, capthick=1, color="magenta")
plt.xlabel("Num. found triplets")
plt.ylabel(r"ChainMaker CPU time [$\mu$s]")
#plt.title("  ChainMaker CPU Performance - Triplets")
plt.legend(loc="best")
plt.xscale("log")
plt.yscale("log")
plt.savefig("binned.png")
plt.show()
