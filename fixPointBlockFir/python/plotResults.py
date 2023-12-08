import numpy as np
import matplotlib.pyplot as plt

def read_pcm_file(file_path):
    with open(file_path, 'rb') as pcm_file:
        # Read the entire content of the file
        pcm_data = pcm_file.read()

        return pcm_data

# Input data.
file_path_input = r"../data/input.pcm"
pcm_input = read_pcm_file(file_path_input)
# Output data.
file_path_output = r"../data/output.pcm"
pcm_output = read_pcm_file(file_path_output)

# Assuming 16-bit signed PCM data
pcm_input_array = np.frombuffer(pcm_input, dtype=np.int16)
pcm_output_array = np.frombuffer(pcm_output, dtype=np.int16)

FFT_input = np.fft.fft(pcm_input_array, 4096)
FFT_output = np.fft.fft(pcm_output_array, 4096)

# Plotting
plt.figure()
# plt.plot(np.abs(FFT_input)[:len(FFT_input)//2], label="Input")
plt.plot(np.abs(FFT_output)[:len(FFT_output)//2], label="Output")
plt.legend()
plt.grid()
plt.show()
