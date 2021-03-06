#include "LibXenoverse.h"

int main(int argc, char** argv)
{
	printf("*******************************************************************\n\
 This tool is for Color/tag some binaries with the help of WxHexEditor (creation of .tags files).\n\
 It's for help to discover/debugging structurs and take care of file format: ema, map, emp, etr, spm, scd.\n\
 Please consider the result as Debug to share information and test if All files are All colored.\n\
 There is also warning when one bytes is taggued 2 time or on overflow, so that could help\n\
 Usage: 'XenoWxHexEditorColorMaker.exe [options] file.ext file2.ext ...'\n\
 Options : '-NoWait', '-AlwaysWait', '-WaitOnError' (default), or '-WaitOnWarning'.\n\
 Notice: by doing a shortcut, you could use another option and keep drag and drop of files.\n\
 Notice: \"path With Spaces\" allowed now. \n\
*******************************************************************\n");

	std::vector<string> arguments = LibXenoverse::initApplication(argc, argv);



	if (arguments.size() == 0)
	{
		printf("Error not enougth arguments.\n");
		LibXenoverse::notifyError();
		LibXenoverse::waitOnEnd();
		return 1;
	}

	
	if (argc < 2)
	{
		printf("Usage: 'XenoWxHexEditorColorMaker.exe [-noEndWait] FILE.EXT FILE2.EXT ...' or 'XenoXmlConverter.exe FILE.EXT.xml FILE2.EXT.xml ...'\nFor Now, we only support map, etr and emp files. Please considere that result as some debug.\n");
		getchar();
		return 1;
	}


	size_t nbArg = arguments.size();
	for (size_t i = 0; i < nbArg; i++)
	{
		string filename = arguments.at(i);
		string extension = LibXenoverse::extensionFromFilename(filename, true);
		string basefilename = filename.substr(0, filename.length() - (extension.size() + 1)) ;
		string extension2 = LibXenoverse::extensionFromFilename(basefilename, true);
		string basefilename2 = basefilename.substr(0, basefilename.length() - (extension2.size() + 1));
		string extension3 = LibXenoverse::extensionFromFilename(basefilename2, true);
		string basefilename3 = basefilename2.substr(0, basefilename2.length() - (extension3.size() + 1));
	

		/////////////////////////////////////////////////////////////
		if (extension == "map")
		{
			LibXenoverse::FmpFile* fmp = new LibXenoverse::FmpFile();
			fmp->save_Coloration(filename);
		}

		/////////////////////////////////////////////////////////////
		if (extension == "etr")							// traces/trails for effects.
		{
			LibXenoverse::Etr* etr = new LibXenoverse::Etr();
			etr->save_Coloration(filename);
		}

		/////////////////////////////////////////////////////////////
		if (extension == "emp")							// particules/mappedPlanes for effects.
		{
			LibXenoverse::EMP* emp = new LibXenoverse::EMP();
			emp->save_Coloration(filename);
		}

		/////////////////////////////////////////////////////////////
		if (extension == "spm")							// particules/mappedPlanes for effects.
		{
			LibXenoverse::Spm* spm = new LibXenoverse::Spm();
			spm->save_Coloration(filename);
		}

		/////////////////////////////////////////////////////////////
		if (extension == "ema")							// particules/mappedPlanes for effects.
		{
			LibXenoverse::EMA* ema = new LibXenoverse::EMA();
			ema->save_Coloration(filename);
		}

		/////////////////////////////////////////////////////////////
		if (extension == "scd")							// dynamique Object (gravity, ...)
		{
			LibXenoverse::Scd* scd = new LibXenoverse::Scd();
			scd->save_Coloration(filename);
		}
	}

	printf("finished.\n");
	LibXenoverse::waitOnEnd();
	return 0;
}