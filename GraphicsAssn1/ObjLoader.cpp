#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include\SOIL.h"

#include "ObjLoader.h"

CObjLoader::CObjLoader ()
{
	/* materials.reserve (100000);

	vertexes.reserve (100000);
	texcoords.reserve (100000);
	normals.reserve (100000);

	parts.reserve (100000);
	*/
	_work_path[0] = 0;
	_loaded = false;
}

bool CObjLoader::Load (char *objfile, char *mtlfile)
{
	bool result = false;
	_splitpath (objfile, NULL, _work_path, NULL, NULL);

	if (mtlfile && *mtlfile) {
		result = loadMaterials (mtlfile);
	}
	if (objfile && *objfile) {
		result = loadObjects (objfile);
	}

	if (!_loaded) {
		loadMaterialsTexture();
		_loaded = true;
	}

	int vt_size = vertexes.size();
	int tc_size = texcoords.size();
	int no_size = normals.size();

	for (int i = 0; i < parts.size(); i++) {
		for (int j = 0; j < parts[i].faces.size(); j++) {
			for (int k = 0; k < parts[i].faces[j].n; k++) {
				int& v = parts[i].faces[j].v[k];
				int& vn = parts[i].faces[j].vn[k];
				int& vt = parts[i].faces[j].vt[k];
				sAllVertex ver;
				if (0 < vn && vn <= no_size) {
					sVertex &no = normals[vn - 1];
					ver.vn = no;
				}
				if (0 < vt && vt <= tc_size) {
					sTexCoord &tc = texcoords[vt - 1];
					ver.vt = tc;
				}
				if (0 < v && v <= vt_size) {
					sVertex &ve = vertexes[v - 1];
					ver.v = ve;
				}
				int* vv = parts[i].faces[j].v;
				sVertex& v0 = vertexes[vv[0] - 1];
				sVertex& v1 = vertexes[vv[1] - 1];
				sVertex& v2 = vertexes[vv[2] - 1];

				int* vvt = parts[i].faces[j].vt;
				sTexCoord& vt0 = texcoords[vvt[0] - 1];
				sTexCoord& vt1 = texcoords[vvt[1] - 1];
				sTexCoord& vt2 = texcoords[vvt[2] - 1];

				vec3 Edge1 = vec3(v1.x, v1.y, v1.z) - vec3(v0.x, v0.y, v0.z);
				vec3 Edge2 = vec3(v2.x, v2.y, v2.z) - vec3(v0.x, v0.y, v0.z);

				float DeltaU1 = vt1.u - vt0.u;
				float DeltaV1 = vt1.v - vt0.v;
				float DeltaU2 = vt2.u - vt0.u;
				float DeltaV2 = vt2.v - vt0.v;

				float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

				sVertex Tangent;
				Tangent.x = f * (DeltaV2 * Edge1.x - DeltaV1 * Edge2.x);
				Tangent.y = f * (DeltaV2 * Edge1.y - DeltaV1 * Edge2.y);
				Tangent.z = f * (DeltaV2 * Edge1.z - DeltaV1 * Edge2.z);

				ver.tangent = Tangent;

				allVertexes.push_back(ver);
			}
			
		}
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, allVertexes.size() * sizeof(sAllVertex), &allVertexes[0], GL_STATIC_DRAW);

	return result;
}

bool CObjLoader::loadObjects (char *fileName)
{
	FILE *fp = fopen (fileName, "r");
	if (!fp) return false;

	// 임시로 사용할 것을 하나 만든다
	//sPart part_;
	//part_.name[0] = 0;
	//parts.push_back (part_);

	//sPart *part = (sPart *)&(*parts.rbegin ());
	sPart *part = NULL;
	char buffer[1024];

	while (fscanf (fp, "%s", buffer) != EOF) {
		bool go_eol = true;

		if (!strncmp ("#", buffer, 1)) {
		}
		else if (!strcmp ("v", buffer)) {
			// Specifies a geometric vertex and its x y z coordinates.
			sVertex v;
			fscanf (fp, "%f %f %f", &v.x, &v.y, &v.z);
			vertexes.push_back (v);
		}
		else if (!strcmp ("vn", buffer)){
			// Specifies a normal vector with components i, j, and k. 
			sVertex v;
			fscanf (fp, "%f %f %f", &v.x, &v.y, &v.z);
			normals.push_back (v);
		}
		else if (!strcmp ("vt", buffer)) {
			// Specifies a texture vertex and its u v coordinates.
			sTexCoord t;
			fscanf (fp, "%f %f", &t.u, &t.v);
			texcoords.push_back (t);
		}
		else if (!strcmp ("f", buffer)){
			// Using v, vt, and vn to represent geometric vertices, texture vertices,
			// and vertex normals, the statement would read:
			//
			//    f v/vt/vn v/vt/vn v/vt/vn v/vt/vn
			sFace f;
			fgets (buffer, 1024, fp);

			char *p = buffer;
			for (int i=0; i<5; ++i) {
				while (*p==' ' || *p=='\t') p++;
				if (*p=='\0' || *p=='\r' || *p=='\n') break;

				f.v[i] = strtoul (p, &p, 10);
				if (*p && *p=='/') { 
					p++;
					f.vt[i] = strtoul (p, &p, 10);
					if (*p && *p=='/') {
						p++;
						f.vn[i] = strtoul (p, &p, 10);
					}
				}
				f.n++;
			}

			if (part) part->faces.push_back (f);
			go_eol = false;
		}
		else if (!strcmp ("usemtl", buffer)) {
			sPart part_;
			
			fscanf (fp, "%s", part_.name);
			parts.push_back (part_);

			part = (sPart *)&(*parts.rbegin ());
		}
		else if (!strcmp ("mtllib", buffer)) {
			fscanf (fp, "%s", buffer);

			char path[MAX_PATH];
			_makepath (path, NULL, _work_path, buffer, NULL);

			loadMaterials (path);
		}
		if (go_eol) fgets (buffer, 1024, fp);
	}
	fclose (fp);
	return true;
}

bool CObjLoader::loadMaterials (char *fileName)
{
	FILE *fp = fopen (fileName, "r");
	if (!fp) return false;

	sMaterial *material = NULL;
	char buffer[1024];

	while (fscanf (fp, "%s", buffer) != EOF) {
		if (!strncmp ("#", buffer, 1)) {
		}
		else if (!strcmp ("newmtl", buffer)){
			sMaterial material_;
			fscanf (fp, "%s", material_.name);

			materials.push_back (material_);
			material = (sMaterial *)&(*materials.rbegin ());
		}
		else if (!strcmp ("Ka", buffer)) {
			// defines the ambient color of the material to be (r,g,b)
			if (material) fscanf (fp, "%f %f %f", &material->Ka[0], &material->Ka[1], &material->Ka[2]);
		}
		else if (!strcmp ("Kd", buffer)) {
			// defines the diffuse reflectivity color of the material to be (r,g,b)
			if (material) fscanf (fp, "%f %f %f", &material->Kd[0], &material->Kd[1], &material->Kd[2]);
		}
		else if (!strcmp ("Ks", buffer)) {
			// defines the specular reflectivity color of the material to be (r,g,b)
			if (material) fscanf (fp, "%f %f %f", &material->Ks[0], &material->Ks[1], &material->Ks[2]);
		}
		else if (!strcmp ("Tf", buffer)) {
			// specify the transmission filter of the current material to be (r,g,b)
			if (material) fscanf (fp, "%f %f %f", &material->Tf[0], &material->Tf[1], &material->Tf[2]);
		}
		else if (!strcmp ("illum", buffer)) {
			// specifies the illumination model to use in the material
			//  "illum_#"can be a number from 0 to 10
			//	 0	Color on and Ambient off
			//	 1	Color on and Ambient on
			//	 2	Highlight on
			//	 3	Reflection on and Ray trace on
			//	 4	Transparency: Glass on Reflection: Ray trace on
			//	 5	Reflection: Fresnel on and Ray trace on
			//	 6	Transparency: Refraction on Reflection: Fresnel off and Ray trace on
			//	 7	Transparency: Refraction on Reflection: Fresnel on and Ray trace on
			//	 8	Reflection on and Ray trace off
			//	 9	Transparency: Glass on Reflection: Ray trace off
			//	 10	Casts shadows onto invisible surfaces
			if (material) fscanf (fp, "%i", &material->illum);
		}
		else if (!strcmp ("map_Kd", buffer)) {
			if (material) fscanf (fp, "%s", material->map_Kd);
		}
		else if (!strcmp("map_bump", buffer)) {
			if (material) fscanf(fp, "%s", material->map_bump);
		}
		else if (!strcmp ("Ns", buffer)) {
			if (material) fscanf (fp, "%f", &material->Ns);
		}
		else if (!strcmp ("Ni", buffer)) {
			if (material) fscanf (fp, "%f", &material->Ni);
		}
		else if (!strcmp ("d", buffer)) {
			if (material) fscanf (fp, "%f", &material->d);
		}
		fgets (buffer, 1024, fp);
	}
	fclose (fp);
	return true;
}

int CObjLoader::findMaterialIndex(char *name)
{
	for (unsigned int i=0; i<materials.size (); ++i) {
		if (!strcmp (name, materials[i].name)) {
			return i;
		}
	}
	return -1;
}

bool CObjLoader::loadTexture(char *fileName, char* nfileName, unsigned int *texture, unsigned int* ntexture)
{
	// http://yamecoder.tistory.com/294
	*texture = SOIL_load_OGL_texture
		(
			fileName,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);

	glBindTexture (GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	*ntexture = SOIL_load_OGL_texture
		(
			nfileName,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);

	glBindTexture(GL_TEXTURE_2D, *ntexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return true;
}

void CObjLoader::loadMaterialsTexture ()
{
	for (unsigned int i=0; i<materials.size (); ++i) {
		if (materials[i].map_Kd[0] && !materials[i].texture) {
			char path[MAX_PATH];
			_makepath (path, NULL, _work_path, materials[i].map_Kd, NULL);
			char npath[MAX_PATH];
			_makepath(npath, NULL, _work_path, materials[i].map_bump, NULL);

			loadTexture (path, npath, &materials[i].texture, &materials[i].nTexture);
		}
	}
}

void CObjLoader::Draw (GLuint shader)
{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(sVertex), &vertexes[0], GL_STATIC_DRAW);

		//extern int lightSourceMode;
		//glBufferSubData(GL_ARRAY_BUFFER, 0, vertexes.size() * sizeof(sVertex), &vertexes[0]);
		
		int stride = sizeof(sVertex) * 3 + sizeof(sTexCoord);
		GLvoid* offset = (GLvoid*) sizeof(sVertex);

		GLint posAttrib = glGetAttribLocation(shader, "pos");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, stride, 0);
		GLint normalAttrib = glGetAttribLocation(shader, "normal");
		GLint coordAttrib = glGetAttribLocation(shader, "TexCoord");
		GLint tangentAttrib = glGetAttribLocation(shader, "tangent");

		glEnableVertexAttribArray(normalAttrib);
		glEnableVertexAttribArray(coordAttrib);
		glEnableVertexAttribArray(tangentAttrib);

		glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, stride, offset);
		offset = (GLvoid*) (sizeof(sVertex) * 2);
		glVertexAttribPointer(coordAttrib, 2, GL_FLOAT, GL_FALSE, stride, offset);
		offset = (GLvoid*)(sizeof(sVertex) * 2 + sizeof(sTexCoord));
		glVertexAttribPointer(tangentAttrib, 3, GL_FLOAT, GL_FALSE, stride, offset);


		vec3 falloff = vec3(0.2);
		vec2 resolution = vec2(WINDOW_WIDTH, WINDOW_HEIGHT);

		vec4 lightpos = vec4(1, 1, 0.5, lightSourceMode);

		glUniform3fv(glGetUniformLocation(shader, "Falloff"), 1, &falloff[0]);
		glUniform2fv(glGetUniformLocation(shader, "Resolution"), 1, &resolution[0]);
		glUniform4fv(glGetUniformLocation(shader, "vLightPos"), 1, &lightpos[0]);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
		for (int i = 0; i < parts.size(); i++) {
			int index = findMaterialIndex(parts[i].name);
			vec4 aColor = vec4(0);
			if (0 <= index) {
				sMaterial &material = materials[index];

				if (material.texture) {
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, material.texture);
					GLint uTexture = glGetUniformLocation(shader, "myTexture");
					if (uTexture != -1) {
						glUniform1i(uTexture, 0);
					}
					else {
						//std::cout << "get texture error" << std::endl;
					}
				}
				if (material.nTexture) {
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, material.nTexture);
					GLint uTexture = glGetUniformLocation(shader, "noTexture");
					if (uTexture != -1) {
						glUniform1i(uTexture, 1);
					}
					else {
						//std::cout << "get ntexture error" << std::endl;
					}
				}
				else {
					//GLint uTexture = glGetUniformLocation(shader, "noTexture");
					//glUniform1i(uTexture, -1);
				}
				vColor = vec3(material.Kd[0], material.Kd[1], material.Kd[2]);
				aColor = vec4(material.Ka[0], material.Ka[1], material.Ka[2], 1.0);
			}
			else {
				vColor = vec3(0.7, 0.7, 0.7);
			}

			GLint uColor = glGetUniformLocation(shader, "uColor");
			if (uColor != -1) {
				glUniform3fv(uColor, 1, &vColor[0]);
			}
			
			glUniform4fv(glGetUniformLocation(shader, "AmbientColor"), 1, &aColor[0]);
			
			
			glDrawArrays(GL_TRIANGLES, 0, allVertexes.size());
			//if(parts[i].vIndices.size() != 0)
			//	glDrawElements(GL_POLYGON, parts[i].vIndices.size(), GL_UNSIGNED_INT, &parts[i].vIndices[0]);
		}
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	

}


