namespace util {

template <class T>
T signum( T value ) {
	return (T( 0 ) < value) - (value < T( 0 ));
}

template <class T>
T sign( T value ) {
	return value < ( T{ 0 } ) ? T( -1 ) : T( 1 );
}

}
