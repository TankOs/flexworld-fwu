namespace util {

template <class T>
int signum( T value ) {
	return (T( 0 ) < value) - (value < T( 0 ));
}

}
