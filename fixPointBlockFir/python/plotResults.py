import wave
import numpy as np
import matplotlib.pyplot as plt


def read_pcm_file(file_path):
    with open(file_path, 'rb') as pcm_file:
        # Read the entire content of the file
        pcm_data = pcm_file.read()

        return pcm_data

def get_sampling_frequency(wav_file_path):
    with wave.open(wav_file_path, 'rb') as wave_file:
        # Get the sample rate from the WAV file
        sample_rate = wave_file.getframerate()
    return sample_rate

if __name__ == "__main__":
    # Getting sampling frequency from input wav file.
    wav_file_path = r"../data/input.wav"
    fs = get_sampling_frequency(wav_file_path)
    print(f"Sampling Frequency: {fs} Hz")

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

    x_axis = np.arange(len(FFT_input)//2) / (len(FFT_input)//2) * fs / 2 / 1e3
    y_axis1 = np.abs(FFT_input)[:len(FFT_input)//2]
    y_axis2 = np.abs(FFT_output)[:len(FFT_output)//2]

    xticks_values = np.linspace(0, fs / 2 / 1e3, 15)
    # Plotting
    plt.figure(figsize = (1920 / 100, 1080 / 100))
    plt.plot(x_axis, y_axis1, label="Input")
    plt.plot(x_axis, y_axis2, label="Output")
    plt.xticks(xticks_values)
    plt.xlabel("Frequency [kHz]")
    plt.ylabel("DFT Amplitude")
    plt.title("Input and output (filtered) spectrum")
    plt.legend()
    plt.grid()

    plt.savefig(r"..\plots\plot.png")

    plt.show()


