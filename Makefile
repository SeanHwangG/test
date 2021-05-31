.PHONY: fix_image
fix_include:
	python3 -m include_file -u seanhwangg -p ~/github/blog -t README.md -y SUMMARY.md --relocate

sync:
	$(foreach PUBLIC, $(PUBLICS), $(shell echo $(PUBLIC)))

remove_prob:
	rm **/.*.prob

remove_empty:
	find . -type d -delete

print_empty:
	find . -empty -print | grep -Ev '__init__|site-packages'
