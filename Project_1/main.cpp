int main(){
	std::string filename;
	std::cout << "Please enter file name:" << std::endl;
	std::cin >> filename;
	workflow(filename); //call workflow class and pass the filename.
}
