uniform int width;
uniform int height;
uniform vec2 ViewSize;
uniform vec2 Transform;
uniform float ZoomFactor;

int SampleFunction(vec2 Point);

void main()
{

    vec2 Pos = vec2(gl_FragCoord.x/float(width), gl_FragCoord.y/float(height));
    Pos = ( (Pos - vec2(0.5, 0.5) ) * vec2(1.0, -1.0) * ViewSize) + Transform;
    float PixelWidth = 1.0/float(width);
    float PixelHeight = 1.0/float(height);
    float LineWidth = 2 * pow(10, ZoomFactor);
    // lookup the pixel in the texture
    vec4 pixel = vec4(1.0,1.0,1.0,1.0);

    int samplecount = 8;
    int Count = 0;
    int NumberofInvalids = 0;
    for(int i = 0; i < samplecount; i++)
    {
        float value = SampleFunction(Pos + vec2(cos(2.0 * 3.14159/samplecount * i) * PixelWidth * LineWidth, sin(2 * 3.14159/samplecount * i) * PixelHeight * LineWidth));

        if(value == 2){
            NumberofInvalids++;   
        }
        else{
          Count += value;
        }
      
        
    }
    float Alias = ((samplecount/2) - abs(Count - samplecount/2)) / (samplecount/2.0);
    if(NumberofInvalids > 0){
        Alias = 0;    
    }
    
    // multiply it by the color
    gl_FragColor = vec4(Alias,0,0,1.0); 
    //no alias 
    if(Alias == 0)
    {
         gl_FragColor = vec4(0,0,0,0); 
    }
}