	def generate_obj(values, k=5):

		h, w = values.shape

		ij = np.meshgrid(np.arange(h), np.arange(w), indexing='ij')
		i = ij[0].reshape(h*w)
		j = ij[1].reshape(h*w)
		values = values.reshape(h*w)

		# Generate list of vertex
		vertex = np.zeros((h*w, 3))
		vertex[:, 0] = i*k
		vertex[:, 1] = j*k
		vertex[:, 2] = values

		# Generate faces
		mask = np.logical_and(i < (h-1), j < (w-1))
		uFaces = np.zeros((h*w, 3), dtype=np.int32)
		indexVertex = np.arange(h*w)+1

		uFaces[mask, 0] = indexVertex[mask]
		uFaces[mask, 1] = indexVertex[mask] + w
		uFaces[mask, 2] = indexVertex[mask] + w + 1
		uFaces = uFaces[mask]

		dFaces = np.zeros((h * w, 3), dtype=np.int32)
		dFaces[mask, 0] = indexVertex[mask] + w + 1
		dFaces[mask, 1] = indexVertex[mask] + 1
		dFaces[mask, 2] = indexVertex[mask]
		dFaces = dFaces[mask]

		faces = np.concatenate((uFaces, dFaces), 0)

		# Generate UV Map
		uvMap = np.zeros((h*w, 2))
		uvMap[:, 0] = j / (w - 1)
		uvMap[:, 1] = 1 - (i / (h - 1))

		# Generate normal faces upperFaces
		#mask = np.logical_and(i > 0, j < h-1)
		aUpper = (np.roll(vertex, h, axis=0) - vertex)
		bUpper = (np.roll(vertex, -1, axis=0) - vertex)

		normalUpperFaces = np.cross(bUpper, aUpper)
		module = np.linalg.norm(normalUpperFaces, axis=1)
		normalUpperFaces[:, 0] = normalUpperFaces[:, 0] / module
		normalUpperFaces[:, 1] = normalUpperFaces[:, 1] / module
		normalUpperFaces[:, 2] = normalUpperFaces[:, 2] / module

		# Generate normal faces downFaces
		#mask = np.logical_and(i < w-1, j > 0)
		aDown = (np.roll(vertex, -h, axis=0) - vertex)
		bDown = (np.roll(vertex, 1, axis=0) - vertex)

		normalDownFaces = np.cross(bDown, aDown)
		module = np.linalg.norm(normalDownFaces, axis=1)
		normalDownFaces[:, 0] = normalDownFaces[:, 0] / module
		normalDownFaces[:, 1] = normalDownFaces[:, 1] / module
		normalDownFaces[:, 2] = normalDownFaces[:, 2] / module

		# Generate vertex normals
		normalVertex = np.zeros((h*w, 3))
		mask = np.logical_and(np.logical_and(i > 0, j > 0), np.logical_and(i < w-1, j < h-1))

		normalVertex = np.roll(normalUpperFaces, 1, axis=0)
		normalVertex += normalUpperFaces
		normalVertex += np.roll(normalUpperFaces, -h, axis=0)
		normalVertex += normalDownFaces
		normalVertex += np.roll(normalDownFaces, h, axis=0)
		normalVertex += np.roll(normalDownFaces, -1, axis=0)

		module = np.linalg.norm(normalVertex, axis=1)
		normalVertex[:, 0] = normalVertex[:, 0] / module
		normalVertex[:, 1] = normalVertex[:, 1] / module
		normalVertex[:, 2] = normalVertex[:, 2] / module

		normalVertex[np.logical_not(mask), 0] = 0
		normalVertex[np.logical_not(mask), 1] = 0
		normalVertex[np.logical_not(mask), 2] = 1

		return vertex, faces, uvMap, normalVertex