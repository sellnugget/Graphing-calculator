type vec4{	
	float x;
	float y;
	float z;
	float w;
}




Shader shader;

fn input(int i) : vec2 {
	vec2 rtn;
	float x = (((i % 100) / 100.0) - 0.5) * 2;
	float y = (((i / 100) / 100.0) - 0.5) * 2;
	rtn.x = x;
	rtn.y = y;
	return rtn;
}
fn perPixel(int value) : vec3 {
	vec2 pos = input(value);

	return vec3(,0,0);
}

TextureBuffer GRAPH;
fn start(){
	GRAPH = TextureBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, VEC3);
}

fn run(){
	
	GRAPH
	drawBuffer(GRAPH, _MAIN);
}
