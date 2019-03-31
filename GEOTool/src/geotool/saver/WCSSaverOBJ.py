from .WCSSaver import WCSSaver


class WCSSaverOBJ(WCSSaver):

	def save(self, file_name, data):

		file = open(file_name+".obj", "w")

		data[data < 0] = 0
		values = data

		result = self.generate_obj(values)
		file.write(result)
		file.close()

	@staticmethod
	def generate_obj(values):
		result = ""

		h, w = values.shape

		# Render vertex
		for i in range(h):
			for j in range(w):
				result += "v {} {} {}\n".format(i, j, values[i][j])

		# Generate faces and vertex textures
		# UV1 - UV2
		# | F1/  |
		# |  / F2|
		# UV3 -- UV4
		count_vt = 1
		for i in range(0, h-1):
			for j in range(0, w-1):
				pos = (i*w)+j+1

				# Generate UV1
				u = (j*1.0)/w
				v = (i*1.0)/h
				result += "vt {} {}\n".format(u, (1-v))

				# Generate UV2
				u = ((j+1) * 1.0) / w
				v = (i * 1.0) / h
				result += "vt {} {}\n".format(u, (1-v))

				# Generate UV3
				u = (j * 1.0) / w
				v = ((i+1) * 1.0) / h
				result += "vt {} {}\n".format(u, (1-v))

				# Generate UV4
				u = ((j+1) * 1.0) / w
				v = ((i+1) * 1.0) / h
				result += "vt {} {}\n".format(u, (1-v))

				# F1
				result += "f {}/{} {}/{} {}/{}\n".format(pos+w, count_vt+2, pos+1, count_vt+1, pos, count_vt)
				# F2
				result += "f {}/{} {}/{} {}/{}\n".format(pos+1, count_vt+1, pos+w, count_vt+2, pos+w+1, count_vt+3)

				count_vt += 4

		return result
