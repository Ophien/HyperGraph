#include "DevilManager.h"

void DevilManager::HandleDevILErrors (){
	ILenum error = ilGetError ();
	if (error != IL_NO_ERROR) {
		do {
			MessageBoxA(NULL,"Erro: ","Devil Error!!!",MB_OK);
			//printf ("\n\n%s\n", iluErrorString (error));	
		} while ((error = ilGetError ()));
		exit (1);
	}
	else
		throw "Erro na janela... removi a lib de erro pq tava dando pau ... so lamento";
}
//deve ser chamado depois que ja criou e associou o contexto OpenGL
void DevilManager::init_after_gl_context_created(){
	if (inited)
		return;
	inited = true;
	//check lib version
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION ||
		iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION ||
		ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION) {
			MessageBoxA(NULL,"DevIL library is out of date! Please upgrade\n","Devil Error!!!",MB_OK);
			throw "DevIL library is out of date! Please upgrade";
			exit(1);
	}
	// Needed to initialize DevIL.
	ilInit ();
	iluInit();
	// GL cannot use palettes anyway, so convert early.
	ilEnable (IL_CONV_PAL);
	// Gets rid of dithering on some nVidia-based cards.
	ilutEnable (ILUT_OPENGL_CONV);
	//somente essa chamada deve ser feita depois de criar e associar o contexto do opengl
	ilutInit();

	ilutEnable(ILUT_GL_GEN_S3TC);

	ilutEnable(ILUT_GL_GEN_S3TC);

	ilEnable(IL_ORIGIN_SET);
	ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);
}

DevilManager::DevilManager(){
	inited = false;
}

DevilManager& DevilManager::getSingleton(){
	static DevilManager devilManager;
	return devilManager;
}
DevilManager* DevilManager::getSingletonPtr(){
	return &getSingleton();
}

GLuint DevilManager::loadTexture(const char* file){
	if (!inited)
		init_after_gl_context_created();
	std::map<std::string,GLuint>::iterator it = string_texture_map.find(file);
	if (it != string_texture_map.end()){
		return it->second;
	}
	char file_aux[MAX_PATH];
	sprintf(file_aux,"%s",file);
	GLuint result = ilutGLLoadImage(file_aux);

	ILenum error = ilGetError ();
	if (error != IL_NO_ERROR)
		throw "erro";

	string_texture_map[file] = result;
	return result;
}

void DevilManager::releaseAllTextures(){
	for (std::map<std::string,GLuint>::iterator it = string_texture_map.begin(); 
		it != string_texture_map.end(); it++){
			glDeleteTextures(1,&it->second);
	}
	string_texture_map.clear();
}
