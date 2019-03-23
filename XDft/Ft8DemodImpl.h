#pragma once
#include "WsjtExe.h"
#include "Ft8Demod.h"
#include <NativeAudioProcessor.h>
struct dec_data;
namespace XDft {
    namespace impl {
        class Ft8DemodImpl
        {
        public:
            Ft8DemodImpl();
            ~Ft8DemodImpl();
            void SetDiskDat(bool);
            bool AddMonoSoundFrames12KHz(const short *p, unsigned count);
            bool Decode(const DecodeClientFcn_t&, WsjtExe);
            unsigned Clock(unsigned tickToTriggerDecode, const DecodeClientFcn_t&f, WsjtExe, 
                bool &invokedDecode, int &cycleNumber);
            unsigned GetSignalSpectrum(float *pSpectrum, int numPoints, float &powerDb);
            void SetAudioSamplesCallback(const AudioCbFcn_t&, unsigned sampleInterval, unsigned sampleCount,
                void *AudioProcessor);

            void set_nfa(int);
            int get_nfa();
            void set_nfb(int);
            int get_nfb();
            void set_n2pass(int);
            int get_n2pass();
            void set_ndepth(int);
            int get_ndepth();
            void set_nfqso(int);
            int get_nfqso();
            void set_nftx(int);
            int get_nftx();
            void set_lft8apon(bool);
            bool get_lft8apon();
            void set_nexp_decode(int);
            int get_nexp_decode();
            void set_mycall(const std::string &);
            std::string get_mycall();
            void set_hiscall(const std::string &);
            std::string get_hiscall();

            void Reset();
        private:
            typedef std::unique_lock<std::mutex> lock_t;
			void CancelCallbackThread();
			void AudioSampleCbThread();
            std::unique_ptr<struct dec_data> m_FortranData;
            unsigned m_sampleCbInterval;
            unsigned m_sampleCbCount;
            unsigned m_lastCalledBackIndex;
            int	 m_decSamplesWritten;
            int  m_TRperiod;
            int  m_Ft8CycleNumber;
            bool m_resetThisInterval;
            bool m_clipSoundToTimepoint;;
            ULARGE_INTEGER m_timepointToTruncate;
            std::shared_ptr<XD::NativeAudioProcessor> m_nativeAudioProcessor;
			AudioCbFcn_t m_audioSamplesCbFcn;
			std::thread m_audioSampleCbThread;
			bool m_audioSampleCbThreadStop;
			std::deque <std::function<void()>> m_audioSampleCbQueue;
			std::condition_variable m_cond;
			std::mutex m_mutex;
        };
    }
}
