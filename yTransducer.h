#ifndef _Y_TRANSDUCER_H_
#define _Y_TRANSDUCER_H_

#include <stdint.h>

#define y_TRANSDUCER_NAME_LEN    (8)

typedef enum _transducer_category_e_ {
	// Transducer category
	T_CATEGORY_TRANSDUCER=    (0),
	T_CATEGORY_SENSOR=        (1),
	T_CATEGORY_ACTUATOR=      (2)
}
y_TCATEGORY_e;

typedef enum _transducer_type_e_ {
	// Transducer types
	T_TYPE_ACCELEROMETER=    (1),
	T_TYPE_GYROSCOPE=        (2),
	T_TYPE_MAGNETOMETER=     (3),
	T_TYPE_ORIENTATION=      (4),
	T_TYPE_PRESSURE=         (5),
	T_TYPE_TEMPERATURE=      (6),
	T_TYPE_HUMIDITY=         (7),
	T_TYPE_VOLTAGE=          (8),
	T_TYPE_CURRENT=          (9),
	T_TYPE_BOOLEAN=         (10)
}
y_TTYPE_e;

typedef struct _transducer_signal_3D_s_ {
	// 3D transducer signal in unified format
	union {
	    /* 3D signal */
	    float v[ 3 ];
	    /* Motion signal */
	    struct {
	        float x;
	        float y;
	        float z;
	    };
	    /* Orientation signal */
	    struct {
	        float pitch;
	        float  roll;
	        float   yaw;
	    };
	};
}
y_TS3D_s;

typedef struct _transducer_spec_s_ {
	// Transducer specification for devices and conversions
	int32_t  version;
	int32_t       id;
	int32_t category;
	int32_t     type;
}
y_TSPEC_s;

typedef struct _transducer_conversion_s_ {
	// Transducer device conversion in unified format (X bytes ?)
	y_TSPEC_s         spec;
	int32_t      timestamp;
	union
	{
	    float           data[ 4 ];
	    y_TS3D_s       accel;
	    y_TS3D_s        gyro;
	    y_TS3D_s         mag;
	    y_TS3D_s orientation;
	    float       pressure;
	    float    temperature;
	    float       humidity;
	    float        voltage;
	    float        current;
	    bool             bit;
	};
}
y_TCONVERSION_s;

typedef struct _transducer_device_s_ {
	// Info about transducer device (Y bytes ?)
	char            name[ y_TRANSDUCER_NAME_LEN ];
	y_TSPEC_s       spec;
	float           vmax;
	float           vmin;
	float     resolution;
	int32_t        delay;
}
y_TDEVICE_s;

class y_TRANSDUCER_c {
	// TRANSDUCER is a DEVICE that CONVERTS energy from one form to another
	public:

	    y_TRANSDUCER_c(   ) {
	    }
	    virtual ~y_TRANSDUCER_c(   ) {
	    }

	    // To be implemented in derived classes
	    virtual bool PerformConversion(
	        y_TCONVERSION_s * conversion
	    )= 0;
	    virtual void InitializeDevice(
	        y_TDEVICE_s * device
	    )= 0;

};

#endif // of _Y_TRANSDUCER_H_
