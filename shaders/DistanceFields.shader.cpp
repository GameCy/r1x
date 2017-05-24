
float udRoundBox( vec3 p, vec3 b, float r )
{
    return length(max(abs(p)-b,0.0))-r;
}

float sdTorus( vec3 p, vec2 t )
{
    return length( vec2(length(p.xz)-t.x,p.y) )-t.y;
}

//------------------------------------------------------------------

float map( in vec3 pos )
{
	//return  sdTorus( pos-vec3(0.0, -0.00, 0.0), vec2(1.00,0.15) );
    return udRoundBox( pos-vec3(0.0, -0.0, 0.0), vec3(0.4,0.2, 0.5), 0.3 );
}

float castRay( in vec3 rayPoint, in vec3 rayDir )
{
    float tmin = 1.0;
    float tmax = 20.0;
   
#if 1
    // bounding volume
    float tp1 = (0.0-rayPoint.y)/rayDir.y;
    if( tp1>0.0 ) 
        tmax = min( tmax, tp1 );
    
    float tp2 = (1.6-rayPoint.y)/rayDir.y; 
    if( tp2>0.0 )
    {
        if( rayPoint.y>1.6 )	tmin = max( tmin, tp2 );
		else					tmax = min( tmax, tp2 ); 
    }
#endif
    
    float t = tmin;
    for( int i=0; i<12; i++ )
    {
	    float precis = 0.0005*t;
	    float res = map( rayPoint+rayDir*t );
        if( res<precis || t>tmax ) break;
        t += res;
    }

    if( t>tmax ) 
        discard;
    return t;
}

vec3 calcNormal( in vec3 pos )
{
    vec2 e = vec2(1.0,-1.0)*0.5773*0.0005;
    return normalize( e.xyy*map( pos + e.xyy ) + 
					  e.yyx*map( pos + e.yyx ) + 
					  e.yxy*map( pos + e.yxy ) + 
					  e.xxx*map( pos + e.xxx ) );
}


vec3 render( in vec3 rayPoint, in vec3 rayDir )
{ 
	vec3 lightDir = normalize( vec3(-0.7, 0.3, -0.6) );
    vec3 col = vec3(1.0);
    float t = castRay(rayPoint,rayDir);
    
    vec3 pos = rayPoint + t*rayDir;
    vec3 normal = calcNormal( pos );
   
    // lighting
    float diffuse = clamp( dot( normal, lightDir ), 0.0, 1.0 );

	vec3 lin = vec3(0.0);
    lin += diffuse;
    lin += vec3(0.40); // ambient
	col = col*lin;    	

	return vec3( clamp(col,0.0,1.0) );
}

mat3 setCamera( in vec3 camPos, in vec3 lookAt, float cr )
{
	vec3 cw = normalize(lookAt - camPos);
	vec3 cp = vec3(sin(cr), cos(cr),0.0);
	vec3 cu = normalize( cross(cw,cp) );
	vec3 cv = normalize( cross(cu,cw) );
    return mat3( cu, cv, cw );
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	float time = 15.0 + iGlobalTime;

	// camera	
    vec3 camPos = vec3( 4.0*cos(time), 3.0 + 5.5*sin(time*3.03)  , sin(time)*6.01 );
    vec3 camLookAt = vec3( 0.0, 0.0, 0.0  );
    mat3 cameraMat = setCamera( camPos, camLookAt, 0.0 );
    
    // -0.5< p <0.5 //
    vec2 p = ( 2.0*fragCoord -iResolution.xy )/iResolution.y;

    // ray direction
    vec3 raydir = cameraMat * normalize( vec3(p.xy,2.0) );
    vec3 col = render( camPos, raydir );

	fragColor = vec4( col, 1.0 );
}

