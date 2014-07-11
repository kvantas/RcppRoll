#include <RcppArmadillo.h>
using namespace Rcpp;

template <class T>
inline double roll_mean(
  const T& x, 
  const NumericVector& weights, 
  const int& n, 
  const int& N, 
  const int& ind) {
    
  double out_ = 0;
	for( int i=0; i < n; i++ ) {
		if( weights[i] != 0 ) {
			out_ += weights[i] * x[i+ind];
		}
	}
	out_ = out_/N;
	return out_;
}

// [[Rcpp::export]]
NumericVector roll_mean_numeric_vector( NumericVector x, int n, NumericVector weights ) {
	
	int len = x.size();
	int len_out = len - n + 1;
	int N = sum( sign( weights*weights ) );
	
	NumericVector out = no_init( len_out );
	
	for( int i=0; i < len_out; i++ ) {
		out[i] = roll_mean(x, weights, n, N, i );
	}
	
	return out;
	
}

// [[Rcpp::export]]
NumericMatrix roll_mean_numeric_matrix( NumericMatrix A, int n, NumericVector weights ) {
	
	int nRow = A.nrow();
	int nCol = A.ncol();
	int N = sum( sign( weights*weights ) );
	
  NumericMatrix B( nRow - n + 1, nCol );
		
	for( int j=0; j < nCol; j++ ) {
		NumericMatrix::Column tmp = A(_, j);
		for( int ind=0; ind < nRow - n + 1; ind++ ) {
			B(ind, j) = roll_mean( tmp, weights, n, N, ind );
		}
	}
	
	return B;
	
}

template <class T>
inline double roll_sum(
  const T& x, 
  const NumericVector& weights, 
  const int& n, 
  const int& N, 
  const int& ind) {
    
  double out_ = 0;
	for( int i=0; i < n; i++ ) {
		if( weights[i] != 0 ) {
			out_ += weights[i] * x[i+ind];
		}
	}
	return out_;
}

// [[Rcpp::export]]
NumericVector roll_sum_numeric_vector( NumericVector x, int n, NumericVector weights ) {
	
	int len = x.size();
	int len_out = len - n + 1;
	int N = sum( sign( weights*weights ) );
	
	NumericVector out = no_init( len_out );
	
	for( int ind=0; ind < len_out; ind++ ) {
		out[ind] = roll_sum(x, weights, n, N, ind );
	}
	
	return out;
	
}

// [[Rcpp::export]]
NumericMatrix roll_sum_numeric_matrix( NumericMatrix A, int n, NumericVector weights ) {
	
	int nRow = A.nrow();
	int nCol = A.ncol();
	int N = sum( sign( weights*weights ) );
	
  NumericMatrix B( nRow - n + 1, nCol );
		
	for( int j=0; j < nCol; j++ ) {
		
		NumericMatrix::Column tmp = A(_, j);
		for( int ind=0; ind < nRow - n + 1; ind++ ) {
			B(ind, j) = roll_sum( tmp, weights, n, N, ind );
		}
	}
	
  return B;
	
} 

template <class T>
inline double roll_var(
  T& x, 
  const NumericVector& weights, 
  const int& n, 
  const int& N, 
  const int& ind) {
    
  double out_ = 0;
  double m = 0;
  
  for( int i=0; i < n; i++ ) {
    if( weights[i] != 0 ) {
      m += x[i+ind];
    }
  }
  
  m = m / N;
  
	for( int i=0; i < n; i++ ) {
		if( weights[i] != 0 ) {
			out_ += weights[i] * ((x[i+ind]-m)*(x[i+ind]-m));
		}
	}
	out_ = out_/(N-1);
	return out_;
}

// [[Rcpp::export]]
NumericVector roll_var_numeric_vector( NumericVector x, int n, NumericVector weights ) {
	
	int len = x.size();
	int len_out = len - n + 1;
	int N = sum( sign( weights*weights ) );
	
	NumericVector out = no_init( len_out );
	
	for( int ind=0; ind < len_out; ind++ ) {
		out[ind] = roll_var(x, weights, n, N, ind );
	}
	
	return out;
	
}

// [[Rcpp::export]]
NumericMatrix roll_var_numeric_matrix( NumericMatrix A, int n, NumericVector weights ) {
	
	int nRow = A.nrow();
	int nCol = A.ncol();
	int N = sum( sign( weights*weights ) );
	
  NumericMatrix B( nRow - n + 1, nCol );
		
	for( int j=0; j < nCol; j++ ) {
		
		NumericMatrix::Column tmp = A(_, j);
		for( int ind=0; ind < nRow - n + 1; ind++ ) {
			B(ind, j) = roll_var( tmp, weights, n, N, ind );
		}
	}
	
  return B;
	
} 

template <class T>
inline double roll_sd(
  const T& x, 
  const NumericVector& weights, 
  const int& n, 
  const int& N, 
  const int& ind) {
    
  double out_ = 0;
	double m = 0;
  
  for( int i=0; i < n; i++ ) {
    if( weights[i] != 0 ) {
      m += x[i+ind];
    }
  }
  
  m = m / N;
  
  for( int i=0; i < n; i++ ) {
		if( weights[i] != 0 ) {
			out_ += weights[i] * ((x[i+ind]-m)*(x[i+ind]-m));
		}
	}
	out_ = sqrt( out_/(N-1) );
	return out_;
}

// [[Rcpp::export]]
NumericVector roll_sd_numeric_vector( NumericVector x, int n, NumericVector weights ) {
	
	int len = x.size();
	int len_out = len - n + 1;
	int N = sum( sign( weights*weights ) );
	
	NumericVector out = no_init( len_out );
	
	for( int ind=0; ind < len_out; ind++ ) {
		out[ind] = roll_sd(x, weights, n, N, ind );
	}
	
	return out;
	
}

// [[Rcpp::export]]
NumericMatrix roll_sd_numeric_matrix( NumericMatrix A, int n, NumericVector weights ) {
	
	int nRow = A.nrow();
	int nCol = A.ncol();
	int N = sum( sign( weights*weights ) );
	
  NumericMatrix B( nRow - n + 1, nCol );
		
	for( int j=0; j < nCol; j++ ) {
		
		NumericMatrix::Column tmp = A(_, j);
		for( int ind=0; ind < nRow - n + 1; ind++ ) {
			B(ind, j) = roll_sd( tmp, weights, n, N, ind );
		}
	}
	
	return B;
	
}


template <class T>
inline double roll_max(
  const T& x, 
  const NumericVector& weights, 
  const int& n, 
  const int& N, 
  const int& ind) {
    
  double out = __DBL_MIN__;
  for( int i=0; i < n; i++ ) {
    if( x[i+ind] > out && weights[i] != 0 ) {
      out = x[i+ind];
    }
  }
  return out;
  
}

// [[Rcpp::export]]
NumericVector roll_max_numeric_vector( NumericVector x, int n, NumericVector weights ) {
  
	int len = x.size();
	int len_out = len - n + 1;
	int N = sum( sign( weights*weights ) );
	
	NumericVector out = no_init( len_out );
	
	for( int ind=0; ind < len_out; ind++ ) {
		out[ind] = roll_max(x, weights, n, N, ind );
	}
	
	return out;
	
}

// [[Rcpp::export]]
NumericMatrix roll_max_numeric_matrix( NumericMatrix A, int n, NumericVector weights ) {
	
	int nRow = A.nrow();
	int nCol = A.ncol();
	int N = sum( sign( weights*weights ) );
	
  NumericMatrix B( nRow - n + 1, nCol );
		
	for( int j=0; j < nCol; j++ ) {
		
		NumericMatrix::Column tmp = A(_, j);
		for( int ind=0; ind < nRow - n + 1; ind++ ) {
			
			B(ind, j) = roll_max( tmp, weights, n, N, ind );
		}
	}
	
  return B;

}

template <class T>
inline double roll_min(
  const T& x, 
  NumericVector& weights, 
  const int& n, 
  const int& N, 
  const int& ind) {
    
  double out = __DBL_MAX__;
  for( int i=0; i < n; i++ ) {
    if( x[i+ind] < out && weights[i] != 0 ) {
      out = x[i+ind];
    }
  }
  return out;
}

// [[Rcpp::export]]
NumericVector roll_min_numeric_vector( NumericVector x, int n, NumericVector weights ) {
  
	int len = x.size();
	int len_out = len - n + 1;
	int N = sum( sign( weights*weights ) );
	
	NumericVector out = no_init( len_out );
	
	for( int ind=0; ind < len_out; ind++ ) {
		out[ind] = roll_min(x, weights, n, N, ind );
	}
	
	return out;
	
}

// [[Rcpp::export]]
NumericMatrix roll_min_numeric_matrix( NumericMatrix A, int n, NumericVector weights ) {
	
	int nRow = A.nrow();
	int nCol = A.ncol();
	int N = sum( sign( weights*weights ) );
	
  NumericMatrix B( nRow - n + 1, nCol );
		
	for( int j=0; j < nCol; j++ ) {
		
		NumericMatrix::Column tmp = A(_, j);
		for( int ind=0; ind < nRow - n + 1; ind++ ) {
			B(ind, j) = roll_min( tmp, weights, n, N, ind );
		}
	}
	
  return B;

}

// [[Rcpp::export]]
NumericVector roll_median_numeric_vector( arma::vec x, int n ) {
	
	int len = x.n_elem;
	int len_out = len - n + 1;
	
	arma::vec out( len_out );
	
	for( int i=0; i < len_out; i++ ) {
		out(i) = arma::median( x.subvec(i, i+n-1) );
	}
	
	return wrap(out);
	
}

// [[Rcpp::export]]
NumericMatrix roll_median_numeric_matrix( arma::mat A, int n, bool by_column ) {
	
	int nRow = A.n_rows;
	int nCol = A.n_cols;
	
	if( by_column ) {
		arma::mat B( nRow - n + 1, nCol );
		
		for( int j=0; j < nCol; j++ ) {
			
			arma::colvec tmp = A.col(j);
			for( int i=0; i < nRow - n + 1; i++ ) {
				B(i, j) = arma::median( tmp.subvec( i, i+n-1 ) );
			}
		}
		
		return wrap(B);
	
	} else {
		
		arma::mat B( nRow, nCol - n + 1 );
		
		for( int i=0; i < nRow; i++ ) {
			
			arma::rowvec tmp = A.row(i);
			for( int j=0; j < nCol - n + 1; j++ ) {
				B(i, j) = arma::median( tmp.subvec( j, j+n-1 ) );
			}
		}
		
		return wrap(B);
	
	}

}

template <class T>
inline double roll_prod(
  const T& x, 
  const NumericVector& weights, 
  const int& n, 
  const int& N, 
  const int& ind) {
    
  double out_ = 1;
	for( int i=0; i < n; i++ ) {
		if( weights[i] != 0 ) {
			out_ *= weights[i] * x[i+ind];
		}
	}
	return out_;
}

// [[Rcpp::export]]
NumericVector roll_prod_numeric_vector( NumericVector x, int n, NumericVector weights ) {
	
	int len = x.size();
	int len_out = len - n + 1;
	int N = sum( sign( weights*weights ) );
	
	NumericVector out = no_init( len_out );
	
	for( int ind=0; ind < len_out; ind++ ) {
		out[ind] = roll_prod(x, weights, n, N, ind );
	}
	
	return out;
	
}

// [[Rcpp::export]]
NumericMatrix roll_prod_numeric_matrix( NumericMatrix A, int n, NumericVector weights ) {
	
	int nRow = A.nrow();
	int nCol = A.ncol();
	int N = sum( sign( weights*weights ) );
	
  NumericMatrix B( nRow - n + 1, nCol );
	
	for( int j=0; j < nCol; j++ ) {
		
		NumericMatrix::Column tmp = A(_, j);
		for( int ind=0; ind < nRow - n + 1; ind++ ) {	
			B(ind, j) = roll_prod( tmp, weights, n, N, ind );
		}
	}
		
	return B;
	
}