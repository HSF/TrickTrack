import matplotlib.pyplot as plt
import scipy.stats
import numpy as np

dat = np.loadtxt("prof_fit_maxnop32.dat")
dat2 = np.loadtxt("prof_fit_maxnop8.dat")
print dat
plt.semilogy(dat[:,0], 10**6 * dat[:,1], 'o', alpha=0.15, color="darkolivegreen", label=r"Max. Matrix dimension $32 \times 32$")
plt.semilogy(dat2[:,0], 10**6 *  dat2[:,1], 's', alpha=0.15, color="mediumslateblue", label=r"Max. Matrix dimension $8 \times 8$")
plt.xlabel("Number of hits in fit")
plt.ylabel(r"Fit CPU time [$\mu$s]")
plt.title("TrickTrack RiemannFit CPU Performance - Random Input")
plt.legend(loc="best")
plt.savefig("tricktrack_riemann_cpu.png")
#plt.savefig("tricktrack_riemann_cpu.pdf")
plt.figure("fitter_binned")
x = dat[:,0]
y = 10**6 * dat[:,1]
means_result = scipy.stats.binned_statistic(x, [y, y**2], 
    bins=range(0, 32), 
    statistic='mean')
count_result = scipy.stats.binned_statistic(x, [y, y**2], 
    bins=range(0, 32), 
    statistic='mean')
means, means2 = means_result.statistic
counts, counts2 = count_result.statistic
standard_deviations = np.sqrt(means2 - means**2)
#standard_deviations = np.sqrt(counts) / counts * means
bin_edges = means_result.bin_edges
bin_centers = (bin_edges[:-1] + bin_edges[1:])/2.
bin_width =  0.5*(bin_edges[1:] - bin_edges[0:-1])
means = np.array(means)

  # do the plot
(_, caps, _) = plt.errorbar(x=bin_centers, y=means, 
      xerr=bin_width, yerr=standard_deviations, 
      linestyle = '', marker='o',capsize=2, capthick=1, color="darkolivegreen" , label=r"Max. Matrix dimension $32 \times 32$")


x = dat2[:,0]
y = 10**6 * dat2[:,1]
means_result = scipy.stats.binned_statistic(x, [y, y**2], 
    bins=range(0, 32), 
    statistic='mean')
count_result = scipy.stats.binned_statistic(x, [y, y**2], 
    bins=range(0, 32), 
    statistic='mean')
means, means2 = means_result.statistic
counts, counts2 = count_result.statistic
standard_deviations = np.sqrt(means2 - means**2)
#standard_deviations = np.sqrt(counts) / counts * means
bin_edges = means_result.bin_edges
bin_centers = (bin_edges[:-1] + bin_edges[1:])/2.
bin_width =  0.5*(bin_edges[1:] - bin_edges[0:-1])
means = np.array(means)

  # do the plot
(_, caps, _) = plt.errorbar(x=bin_centers, y=means, 
      xerr=bin_width, yerr=standard_deviations, 
      linestyle = '', marker='o',capsize=2, capthick=1, color="mediumslateblue" , label=r"Max. Matrix dimension $8 \times 8$")

plt.xlabel("Number of hits in fit")
plt.ylabel(r"Fit CPU time [$\mu$s]")
#plt.title("TrickTrack RiemannFit CPU Performance - Random Input")
plt.yscale("log")
plt.legend(loc="best")
plt.savefig("tricktrack_riemann_cpu_binned.png")
plt.show()
