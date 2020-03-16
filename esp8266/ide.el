;; This buffer is for text that is not saved, and for Lisp evaluation.
;; To create a file, visit it with C-x C-f and enter text in its buffer.

(defun build()
  (interactive)
  (let ((old-pwd (eshell/pwd)))
    (cd "~/kameleon/esp32")
    (compile "idf.py build")
    (cd old-pwd)))


	
