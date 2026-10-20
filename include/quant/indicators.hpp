#pragma once

#include <cstddef>
#include <vector>

/// \file quant/indicators.hpp
/// \brief Small library of quantitative-finance indicators used in the
///        "Software Engineering and C++ for quantitative analysis and
///        algorithmic trading" course project.

namespace quant {

/// \brief Computes the simple moving average (SMA) of a price series.
///
/// For every index \f$i\f$ the result is the arithmetic mean of
/// \f$\text{prices}[i-\text{window}+1 \ldots i]\f$. The first
/// <tt>window - 1</tt> entries have no complete window and are set to
/// <tt>NaN</tt>. If \p window is larger than the number of prices, every
/// entry is <tt>NaN</tt>.
///
/// \param prices Sequence of prices (e.g. daily closing prices).
/// \param window Size of the averaging window; must be > 0.
/// \return A vector of the same size as \p prices.
/// \throws std::invalid_argument if \p window == 0.
std::vector<double> simple_moving_average(const std::vector<double>& prices,
                                          std::size_t window);

/// \brief Computes daily (period-over-period) returns of a price series.
///
/// Return value \f$r_i = \frac{\text{prices}[i] - \text{prices}[i-1]}
/// {\text{prices}[i-1]}\f$ for \f$i = 1 \ldots n-1\f$.
///
/// \param prices Sequence of prices, must be non-empty.
/// \return A vector with <tt>prices.size() - 1</tt> entries (empty when the
///         input has fewer than 2 elements).
std::vector<double> daily_returns(const std::vector<double>& prices);

} // namespace quant
