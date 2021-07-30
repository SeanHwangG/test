.PHONY: fix_image
fix_include:
	python3 -m include_file -u seanhwangg -p ~/github/blog -toc table_of_contents.md -y SUMMARY.md --relocate --stem

remove_prob:
	rm **/.*.prob

print_empty:
	find . -empty -print | grep -Ev '__init__|site-packages|private|node_modules'

delete_empty:
	make print_empty | xargs -I {} rmdir {}
