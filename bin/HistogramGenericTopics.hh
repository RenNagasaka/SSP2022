#ifndef _interface_bril_HistogramGenericTopics_hh_
#define _interface_bril_HistogramGenericTopics_hh_
#include "cmath"

namespace interface{
    namespace bril{

        // basic methods
        namespace histogramgeneric {
            // methods
            constexpr uint32_t calculate_counter_nwords(uint32_t pNbins, uint32_t pCounterWidth) { if (pCounterWidth <= 16) { return pNbins/2; } else { return pNbins; } }
            constexpr uint32_t calculate_error_payload_size(uint32_t pNunits) { return 4 + 16 + 16 + pNunits; }
            constexpr uint32_t calculate_mask_nwords(uint32_t pNunits) { if (pNunits > 1) { return std::pow(2, std::ceil(std::log2(int((calculate_error_payload_size(pNunits) + 31)/32)))); } else return 0; } // no errors if a single module
            constexpr uint32_t calculate_error_max_nwords(uint32_t pNunits, uint32_t pErrorCounterWidth) { if (pNunits > 1) { return pNunits * calculate_mask_nwords(pNunits) * std::pow(2,pErrorCounterWidth); } else return 0; } // no errors if a single module
            constexpr uint32_t calculate_max_size(uint32_t pHeaderSize, uint32_t pNbins, uint32_t pCounterWidth, uint32_t pNunits, uint32_t pErrorCounterWidth) { return pHeaderSize + calculate_counter_nwords(pNbins, pCounterWidth) + calculate_mask_nwords(pNunits) + calculate_error_max_nwords(pNunits, pErrorCounterWidth); }

            // define default struct which contains all the expected histograms info
            struct HistogramGenericParametersT {
                uint32_t fHeaderSize;
                uint32_t fNbins;
                uint32_t fCounterWidth;
                uint32_t fIncrementWidth;
                uint32_t fNunits;
                uint32_t fUnitIncrementWidth;
                uint32_t fErrorCounterWidth;
                uint32_t fCounterNwords = histogramgeneric::calculate_counter_nwords(fNbins, fCounterWidth);
                uint32_t fErrorPayloadSize = histogramgeneric::calculate_error_payload_size(fNunits);
                uint32_t fMaskNwords = histogramgeneric::calculate_mask_nwords(fNunits);
                uint32_t fErrorMaxNwords = histogramgeneric::calculate_error_max_nwords(fNunits, fErrorCounterWidth);
                uint32_t fMaxSize = histogramgeneric::calculate_max_size(fHeaderSize, fNbins, fCounterWidth, fNunits, fErrorCounterWidth);
            };
        }

        constexpr histogramgeneric::HistogramGenericParametersT HISTOGRAMGENERIC_PARAMETERS = {.fHeaderSize = 9,
                                                                                                .fNbins = 3564,
                                                                                                .fCounterWidth = 21,
                                                                                                .fIncrementWidth = 7,
                                                                                                .fNunits = 39,
                                                                                                .fUnitIncrementWidth = 2,
                                                                                                .fErrorCounterWidth = 3};

    }
}

#endif
