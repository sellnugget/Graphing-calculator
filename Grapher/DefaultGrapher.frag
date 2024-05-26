uniform int width;
uniform int height;
uniform float a;
uniform vec2 Transform;
uniform float ZoomFactor;


int SampleFunction(vec2 Point);

void main()
{
    vec2 Pos = ((gl_TexCoord[0].xy - vec2(0.5, 0.5)) * vec2(2.0, -2.0) + Transform) * pow(10, ZoomFactor);
    float PixelWidth = 1.0/float(width);
    float PixelHeight = 1.0/float(height);


    float LineWidth = 4 * pow(10, ZoomFactor);
    // lookup the pixel in the texture
    vec4 pixel = vec4(1.0,1.0,1.0,1.0);

    int samplecount = 8;
    int Count = 0;
    for(int i = 0; i < samplecount; i++)
    {
        Count += SampleFunction(Pos + vec2(cos(2.0 * 3.14159/samplecount * i) * PixelWidth * LineWidth, sin(2 * 3.14159/samplecount * i) * PixelHeight * LineWidth));
    }
    float Alias = ((samplecount/2) - abs(Count - samplecount/2)) / (samplecount/2.0);
    // multiply it by the color
    gl_FragColor = vec4(Alias,Alias,Alias,1.0); 
    //no alias 
    if(Alias != 0)
    {
        gl_FragColor = vec4(1,0,0,1); 
    }
    else
    {
        gl_FragColor = vec4(0,0,0,0); 
    }
}