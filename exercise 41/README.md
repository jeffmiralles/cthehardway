optimize @ bstrlib.c  bstrcmp function

//from exercise 40 not optimize
727,508  src/lcthw/bstrlib.c:bstrcmp [tests/bstree_tests]  //without assert
280,517      if (b0 == NULL || b1 == NULL || b0->data == NULL || b1->data == NULL ||
.          b0->slen < 0 || b1->slen < 0) return SHRT_MIN;   ===IR===


//exercise 41 optimize cuts ~= 200,000 IR
533,906  src/lcthw/bstrlib.c:bstrcmp [tests/bstree_tests] with assert
.      assert (b0 == NULL || b1 == NULL || b0->data == NULL || b1->data == NULL ||
.          b0->slen < 0 || b1->slen < 0);

