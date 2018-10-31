#ifndef IPARAM_H
#define IPARAM_H

typedef double real_Double_t;

#define PASTE_CODE_FREE_MATRIX(_desc_)                                  \
    if ( _desc_ != NULL ) {                                             \
        free(_desc_->mat);                                              \
    }                                                                   \
    PLASMA_Desc_Destroy( &_desc_ );

/*********************
 *
 * General Macros for timing
 *
 */
#define START_TIMING()                          \
  t = -cWtime();

#define STOP_TIMING()                           \
  t += cWtime();                                \
  *t_ = t;

#endif /* IPARAM_H */
