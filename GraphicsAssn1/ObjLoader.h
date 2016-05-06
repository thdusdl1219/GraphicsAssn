#include "default.h"
#include <vector>

using namespace std;

struct sVertex
{
	float x, y, z;
};

struct sTexCoord
{
	float u, v;
};

struct sAllVertex
{
	sVertex v;
	sVertex vn;
	sTexCoord vt;
	sVertex tangent;
};

struct sMaterial
{	
	char name[256];
	int illum;
	char map_Kd[256];
	char map_bump[256];
	float Ns;
	float Ni;
	float d;
	float Ka[3];
	float Kd[3];
	float Ks[3];
	float Tf[3];
	unsigned int texture;
	unsigned int nTexture;

	sMaterial() {
		memset (this, 0, sizeof(sMaterial));
	}
};

struct sFace
{
	int n;

	int v[5];	//vertices
	int vt[5];	//text coords
	int vn[5];	//normals

	sFace() {
		memset (this, 0, sizeof(sFace));
	}
};

struct sPart
{
	char name[256];
	
	//vector<int> vIndices;
	vector<sFace> faces;

	sPart() {
		name[0] = 0;
	}
};

class CObjLoader
{
public:
	CObjLoader ();

	void loadMaterialsTexture ();
	bool Load (char *objfile, char *mtlfile = NULL);
	
	void Draw (GLuint);
	void Draw_Object(GLuint);


	vector<sAllVertex> allVertexes;
	

private:
	vector<sMaterial> materials;
	GLuint vbo;
	vector<sVertex> vertexes;
	vector<sTexCoord> texcoords;
	vector<sVertex> normals;
	vector<sPart> parts;

	bool loadObjects (char *fileName);
	bool loadMaterials (char *fileName);

	int findMaterialIndex(char *name);
	bool loadTexture (char *fileName, char*, unsigned int *texture, unsigned int*);

private:	
	vec3 vColor;
	char _work_path[_MAX_DIR];
	bool _loaded;
};
