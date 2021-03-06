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

#ifndef _linear_algebra_detail_device_cublas_Matrix_h
#define _linear_algebra_detail_device_cublas_Matrix_h

#include <linear_algebra/Matrix.h>

#include "Array.h"

namespace linear_algebra
{
    namespace detail
    {
	namespace device
	{
	    namespace cublas
	    {
		/**
		   Matrix structure for cublas
		*/
		template < typename Atom >
		class Matrix : public Array< Atom >, virtual public linear_algebra::Matrix< Atom >
		{
		    using Array< Atom >::_deviceArray;
		    using Array< Atom >::_size;

		public:
		    using Array< Atom >::operator=;

		    //! main ctor
		    Matrix() {}

		    //! ctor to define matrix size (n*n)
		    Matrix(int n) : Array< Atom >(n*n), _n(n), _m(n) {}

		    //! ctor to define matrix size (n*n) and value to set to each element of the matrix
		    Matrix(int n, Atom value) : Array< Atom >(n*n, value), _n(n), _m(n) {}

		    //! ctor to define matrix size (n*m) and value to set to each element of the matrix
		    Matrix(int n, int m, Atom value) : Array< Atom >(n*m, value), _n(n), _m(m) {}

		    //! class name
		    std::string className() const { return "Matrix"; }

		    //! print the whole content of the matrix
		    virtual void printOn(std::ostream& _os) const
		    {
			if ( !_deviceArray ) { return; }
			if ( _size <= 0 ) { return; }

			Atom* hostArray;
			createHostArray( hostArray, _size );

			CUBLAS_CALL( cublasGetVector(_size, sizeof(*_deviceArray), _deviceArray, 1, hostArray, 1) );

			for ( int i = 0; i < _n; ++i )
			    {
				_os << "[" << *(hostArray + i*_n);
				for ( int j = 0; j < _m; ++j )
				    {
					_os << ", " << *(hostArray + i*_n + j);
				    }
				_os << "]" << std::endl;
			    }

			destroyHostArray(hostArray);
		    }

		    //! to get number of rows
		    inline int rows() const { return _n; }

		    //! to get number of columns
		    inline int cols() const { return _m; }

		    //! to resize matrix size
		    void resize(int n, int m) { Array< Atom >::resize(n*m); }

		private:
		    int _n;
		    int _m;
		};
	    }
	}
    }
}

#endif // !_linear_algebra_detail_device_cublas_Matrix_h
