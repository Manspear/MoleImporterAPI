#pragma once
//cout << "Mesh: " << i << endl;
//
//infile.read((char*)&read_meshList[i], sizeof(read_sMesh));//													Information av hur många vertices som senare kommer att komma, och efter det hur många skelAnim verticear som kommer komma osv, samt hur mycket minne den inten som berättar detta tar upp(reservation för vår header).En int kommer först, den har värdet 100.  Och den inten kommer ta upp 4 bytes.
//
//cout << "Mesh vector: " << endl;
//
//cout << "\t";
//cout << "xyz: ";
//cout << read_meshList[i].translate[0];
//cout << read_meshList[i].translate[1];
//cout << read_meshList[i].translate[2] << endl;
//
//cout << "\t";
//cout << "rot: ";
//cout << read_meshList[i].rotation[0];
//cout << read_meshList[i].rotation[1];
//cout << read_meshList[i].rotation[2] << endl;
//
//cout << "\t";
//cout << "scale: ";
//cout << read_meshList[i].scale[0];
//cout << read_meshList[i].scale[1];
//cout << read_meshList[i].scale[2] << endl;
//
//cout << "\t";
//cout << "Vertex Count: ";
//cout << read_meshList[i].vertexCount << endl;
////cout << "SkelAnimVert Count: 0" << endl;
////cout << "Joint Count: 0"  << endl;
//
//cout << "\t";
//cout << "Material ID: ";
//cout << read_meshList[i].materialID << endl;
////detta är storleken av innehållet i vList.data()
//
//cout << "\n";
//cout << "Vertex vector: " << endl;
//
//cout << "mlist: " << endl;
//read_mList[i].vList.resize(read_meshList[i].vertexCount);
//cout << "\t";
//cout << read_mList[i].vList.data() << endl;
//
//cout << "\t";
//cout << "Allocated memory for " << read_meshList[i].vertexCount << " vertices" << endl;
//
//
//read_mList[i].vList.resize(read_meshList[i].vertexCount);
//
//infile.read((char*)read_mList[i].vList.data(), sizeof(read_sVertex) * read_meshList[i].vertexCount);//				Skriver ut alla vertices i får vArray, pos, nor, rgba 100 gånger. Och minnet 100 Vertices tar upp.
//
//																									//cout << "SkelAnimVert vector: NULL" << endl;
//
