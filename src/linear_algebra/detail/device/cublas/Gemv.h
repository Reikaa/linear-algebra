// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 * Caner Candan <caner@candan.fr>, http://caner.candan.fr
 */

#ifndef _linear_algebra_detail_device_cublas_Gemv_h
#define _linear_algebra_detail_device_cublas_Gemv_h

#include <cublas.h>

#include <linear_algebra/detail/device/cuda/cuda>

#include "MultiplyMatVecOp.h"

namespace linear_algebra
{
    namespace detail
    {
	namespace device
	{
	    namespace cublas
	    {
		/**
		   Gemv operator
		*/
		template < typename Atom >
		class Gemv : public MultiplyMatVecOp< Atom >
		{
		public:
		    //! main function
		    void operator()( const Matrix< Atom >&, const Vector< Atom >&, Vector< Atom >& );
		};

		/**
		   main function specialized for single precision
		*/
		template <>
		void Gemv< float >::operator()( const Matrix< float >& A, const Vector< float >& x, Vector< float >& y )
		{
		    int n = A.rows();
		    int m = A.cols();
		    cublasSgemv('n', m, n, 1, A, m, x, 1, 0, y, 1);
		}

		/**
		   main function specialized for double precision
		*/
		template <>
		void Gemv< double >::operator()( const Matrix< double >& A, const Vector< double >& x, Vector< double >& y )
		{
		    int n = A.rows();
		    int m = A.cols();
		    cublasDgemv('n', m, n, 1, A, m, x, 1, 0, y, 1);
		}

		/**
		   main function specialized for single precision complex number
		*/
		template <>
		void Gemv< cuda::SingleComplex >::operator()( const Matrix< cuda::SingleComplex >& A, const Vector< cuda::SingleComplex >& x, Vector< cuda::SingleComplex >& y )
		{
		    int n = A.rows();
		    int m = A.cols();
		    cublasCgemv('n', m, n, cuda::SingleComplex(1), A, m, x, 1, cuda::SingleComplex(0), y, 1);
		}

		/**
		   main function specialized for double precision complex number
		*/
		template <>
		void Gemv< cuda::DoubleComplex >::operator()( const Matrix< cuda::DoubleComplex >& A, const Vector< cuda::DoubleComplex >& x, Vector< cuda::DoubleComplex >& y )
		{
		    int n = A.rows();
		    int m = A.cols();
		    cublasZgemv('n', m, n, cuda::DoubleComplex(1), A, m, x, 1, cuda::DoubleComplex(0), y, 1);
		}
	    }
	}
    }
}

#endif // !_linear_algebra_detail_device_cublas_Gemv_h
