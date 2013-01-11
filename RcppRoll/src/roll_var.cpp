#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector roll_var_numeric_vector( NumericVector x, int n ) {
	
	int len = x.size();
	int len_out = len - n + 1;
	
	NumericVector out = no_init( len_out );
	
	for( int i=0; i < len_out; i++ ) {
		out[i] = var( x[ seq(i, i+n-1) ] );
	}
	
	return out;
	
}

// [[Rcpp::export]]
NumericMatrix roll_var_numeric_matrix( NumericMatrix A, int n ) {
	
	int nRow = A.nrow();
	int nCol = A.ncol();
	
	NumericMatrix B( nRow - n + 1, nCol );
	
	for( int j=0; j < nCol; j++ ) {
		
		NumericVector tmp = A(_, j);
		for( int i=0; i < nRow - n + 1; i++ ) {
			B(i, j) = var( tmp[ seq(i, i+n-1) ] );
		}
	}
	
	return B;
	
}
