#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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
	for (int i = 0; i < parts.size(); i++) {
		for (int j = 0; j < parts[i].faces.size(); j++) {
			int* v = parts[i].faces[j].v;
			parts[i].vIndices.push_back(v[0]);
			parts[i].vIndices.push_back(v[1]);
			parts[i].vIndices.push_back(v[2]);
		}
	}
/*
	int vt_size = vertexes.size();
	int tc_size = texcoords.size();
	int no_size = normals.size();
	

	for (unsigned int h = 0; h < parts.size(); ++h) {
		int index = findMaterialIndex(parts[h].name);
		vector<sFace> &faces = parts[h].faces;

		if (0 <= index) {
			sMaterial &material = materials[index];

			if (material.texture) {
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, material.texture);
			}
			else {
				// glColor3f(material.Kd[0], material.Kd[1], material.Kd[2]);
				vColor = vec3(material.Kd[0], material.Kd[1], material.Kd[2]);
			}
		}
		else {
			// glColor3f(0.7f, 0.7f, 0.7f);
			vColor = vec3(0.7f, 0.7f, 0.7f);
		}


		for (unsigned int i = 0, ip = faces.size(); i < ip; ++i) {
			//glBegin (GL_POLYGON);

			for (int j = 0, jn = faces[i].n; j < jn; ++j) {
				int &v = faces[i].v[j];
				int &vt = faces[i].vt[j];
				int &vn = faces[i].vn[j];

				/*if (0 < vn && vn <= no_size) {
				sVertex &no = normals[vn - 1];
				glNormal3f (no.x, no.y, no.z);
				}
				if (0 < vt && vt <= tc_size) {
				sTexCoord &tc = texcoords[vt - 1];
				glTexCoord2f (tc.u, tc.v);
				}
				if (0 < v && v <= vt_size) {
					sVertex &vt = vertexes[v - 1];
					vertices.push_back(vec3(vt.x, vt.y, vt.x));
					//					glVertex3f (scale*vt.x, scale*vt.y, scale*vt.z);
				}
			}
			//glEnd ();  
		}
	}
	*/
	return result;
}

bool CObjLoader::loadObjects (char *fileName)
{
	FILE *fp = fopen (fileName, "r");
	if (!fp) return false;

	// 임시로 사용할 것을 하나 만든다
	sPart part_;
	part_.name[0] = 0;
	parts.push_back (part_);

	sPart *part = (sPart *)&(*parts.rbegin ());
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

bool CObjLoader::loadTexture (char *fileName, unsigned int *texture)
{
	/* IplImag *img = cvLoadImage (fileName);
	if (!img) return false;

	cvFlip (img, img);

	glGenTextures (1, texture);
	glBindTexture (GL_TEXTURE_2D, *texture);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D (GL_TEXTURE_2D, 0, 3, img->width, img->height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, img->imageData);

	cvReleaseImage (&img);*/
	return true;
}

void CObjLoader::loadMaterialsTexture ()
{
	for (unsigned int i=0; i<materials.size (); ++i) {
		if (materials[i].map_Kd[0] && !materials[i].texture) {
			char path[MAX_PATH];
			_makepath (path, NULL, _work_path, materials[i].map_Kd, NULL);

			loadTexture (path, &materials[i].texture);
		}
	}
}

void CObjLoader::Draw (GLuint shader)
{
		GLint uColor = glGetUniformLocation(shader, "uColor");
		if (uColor != -1) {
			glUniform3fv(uColor, 1, &vColor[0]);
		}
		else {
			std::cout << "get color error" << std::endl;
		}

		glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(sVertex), &vertexes[0], GL_STATIC_DRAW);
		GLint posAttrib = glGetAttribLocation(shader, "pos");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		for (int i = 0; i < parts.size(); i++) {
			if(parts[i].vIndices.size() != 0)
				glDrawElements(GL_POLYGON, parts[i].vIndices.size(), GL_UNSIGNED_INT, &parts[i].vIndices[0]);
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	

}


