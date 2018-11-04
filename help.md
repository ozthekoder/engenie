# Objects
* [`Accessor`](#reference-accessor)
   * [`Sparse`](#reference-accessor-sparse)
      * [`Indices`](#reference-accessor-sparse-indices)
      * [`Values`](#reference-accessor-sparse-values)
* [`Animation`](#reference-animation)
   * [`Channel`](#reference-animation-channel)
      * [`Target`](#reference-animation-channel-target)
   * [`Sampler`](#reference-animation-sampler)
* [`Asset`](#reference-asset)
* [`Buffer`](#reference-buffer)
* [`Buffer View`](#reference-buffer-view)
* [`Camera`](#reference-camera)
   * [`Orthographic`](#reference-camera-orthographic)
   * [`Perspective`](#reference-camera-perspective)
* [`Extension`](#reference-extension)
* [`Extras`](#reference-extras)
* [`glTF`](#reference-gltf) (root object)
* [`glTF Child of Root Property`](#reference-gltf-child-of-root-property)
* [`glTF Id`](#reference-gltf-id)
* [`glTF Property`](#reference-gltf-property)
* [`Image`](#reference-image)
* [`Material`](#reference-material)
   * [`Normal Texture Info`](#reference-material-normal-texture-info)
   * [`Occlusion Texture Info`](#reference-material-occlusion-texture-info)
   * [`PBR Metallic Roughness`](#reference-material-pbr-metallic-roughness)
* [`Mesh`](#reference-mesh)
   * [`Primitive`](#reference-mesh-primitive)
* [`Node`](#reference-node)
* [`Sampler`](#reference-sampler)
* [`Scene`](#reference-scene)
* [`Skin`](#reference-skin)
* [`Texture`](#reference-texture)
* [`Texture Info`](#reference-texture-info)


---------------------------------------
<a name="reference-accessor"></a>
## Accessor

A typed view into a bufferView.  A bufferView contains raw binary data.  An accessor provides a typed view into a bufferView or a subset of a bufferView similar to how WebGL's `vertexAttribPointer()` defines an attribute in a buffer.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**bufferView**|`integer`|The index of the bufferView.|No|
|**byteOffset**|`integer`|The offset relative to the start of the bufferView in bytes.|No, default: `0`|
|**componentType**|`integer`|The datatype of components in the attribute.| :white_check_mark: Yes|
|**normalized**|`boolean`|Specifies whether integer data values should be normalized.|No, default: `false`|
|**count**|`integer`|The number of attributes referenced by this accessor.| :white_check_mark: Yes|
|**type**|`string`|Specifies if the attribute is a scalar, vector, or matrix.| :white_check_mark: Yes|
|**max**|`number` `[1-16]`|Maximum value of each component in this attribute.|No|
|**min**|`number` `[1-16]`|Minimum value of each component in this attribute.|No|
|**sparse**|`object`|Sparse storage of attributes that deviate from their initialization value.|No|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### accessor.bufferView

The index of the bufferView. When not defined, accessor must be initialized with zeros; `sparse` property or extensions could override zeros with actual values.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### accessor.byteOffset

The offset relative to the start of the bufferView in bytes.  This must be a multiple of the size of the component datatype.

* **Type**: `integer`
* **Required**: No, default: `0`
* **Minimum**: ` >= 0`
* **Related WebGL functions**: `vertexAttribPointer()` offset parameter

### accessor.componentType :white_check_mark: 

The datatype of components in the attribute.  All valid values correspond to WebGL enums.  The corresponding typed arrays are `Int8Array`, `Uint8Array`, `Int16Array`, `Uint16Array`, `Uint32Array`, and `Float32Array`, respectively.  5125 (UNSIGNED_INT) is only allowed when the accessor contains indices, i.e., the accessor is only referenced by `primitive.indices`.

* **Type**: `integer`
* **Required**: Yes
* **Allowed values**:
   * `5120` BYTE
   * `5121` UNSIGNED_BYTE
   * `5122` SHORT
   * `5123` UNSIGNED_SHORT
   * `5125` UNSIGNED_INT
   * `5126` FLOAT
* **Related WebGL functions**: `vertexAttribPointer()` type parameter

### accessor.normalized

Specifies whether integer data values should be normalized (`true`) to [0, 1] (for unsigned types) or [-1, 1] (for signed types), or converted directly (`false`) when they are accessed. This property is defined only for accessors that contain vertex attributes or animation output data.

* **Type**: `boolean`
* **Required**: No, default: `false`
* **Related WebGL functions**: `vertexAttribPointer()` normalized parameter

### accessor.count :white_check_mark: 

The number of attributes referenced by this accessor, not to be confused with the number of bytes or number of components.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 1`

### accessor.type :white_check_mark: 

Specifies if the attribute is a scalar, vector, or matrix.

* **Type**: `string`
* **Required**: Yes
* **Allowed values**:
   * `"SCALAR"`
   * `"VEC2"`
   * `"VEC3"`
   * `"VEC4"`
   * `"MAT2"`
   * `"MAT3"`
   * `"MAT4"`

### accessor.max

Maximum value of each component in this attribute.  Array elements must be treated as having the same data type as accessor's `componentType`. Both min and max arrays have the same length.  The length is determined by the value of the type property; it can be 1, 2, 3, 4, 9, or 16.

`normalized` property has no effect on array values: they always correspond to the actual values stored in the buffer. When accessor is sparse, this property must contain max values of accessor data with sparse substitution applied.

* **Type**: `number` `[1-16]`
* **Required**: No

### accessor.min

Minimum value of each component in this attribute.  Array elements must be treated as having the same data type as accessor's `componentType`. Both min and max arrays have the same length.  The length is determined by the value of the type property; it can be 1, 2, 3, 4, 9, or 16.

`normalized` property has no effect on array values: they always correspond to the actual values stored in the buffer. When accessor is sparse, this property must contain min values of accessor data with sparse substitution applied.

* **Type**: `number` `[1-16]`
* **Required**: No

### accessor.sparse

Sparse storage of attributes that deviate from their initialization value.

* **Type**: `object`
* **Required**: No

### accessor.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### accessor.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### accessor.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-accessor-sparse"></a>
## Accessor Sparse

Sparse storage of attributes that deviate from their initialization value.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**count**|`integer`|Number of entries stored in the sparse array.| :white_check_mark: Yes|
|**indices**|`object`|Index array of size `count` that points to those accessor attributes that deviate from their initialization value. Indices must strictly increase.| :white_check_mark: Yes|
|**values**|`object`|Array of size `count` times number of components, storing the displaced accessor attributes pointed by `indices`. Substituted values must have the same `componentType` and number of components as the base accessor.| :white_check_mark: Yes|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### accessor.sparse.count :white_check_mark: 

The number of attributes encoded in this sparse accessor.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 1`

### accessor.sparse.indices :white_check_mark: 

Index array of size `count` that points to those accessor attributes that deviate from their initialization value. Indices must strictly increase.

* **Type**: `object`
* **Required**: Yes

### accessor.sparse.values :white_check_mark: 

Array of size `count` times number of components, storing the displaced accessor attributes pointed by `indices`. Substituted values must have the same `componentType` and number of components as the base accessor.

* **Type**: `object`
* **Required**: Yes

### accessor.sparse.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### accessor.sparse.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-accessor-sparse-indices"></a>
## Accessor Sparse Indices

Indices of those attributes that deviate from their initialization value.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**bufferView**|`integer`|The index of the bufferView with sparse indices. Referenced bufferView can't have ARRAY_BUFFER or ELEMENT_ARRAY_BUFFER target.| :white_check_mark: Yes|
|**byteOffset**|`integer`|The offset relative to the start of the bufferView in bytes. Must be aligned.|No, default: `0`|
|**componentType**|`integer`|The indices data type.| :white_check_mark: Yes|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### accessor.sparse.indices.bufferView :white_check_mark: 

The index of the bufferView with sparse indices. Referenced bufferView can't have ARRAY_BUFFER or ELEMENT_ARRAY_BUFFER target.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 0`

### accessor.sparse.indices.byteOffset

The offset relative to the start of the bufferView in bytes. Must be aligned.

* **Type**: `integer`
* **Required**: No, default: `0`
* **Minimum**: ` >= 0`

### accessor.sparse.indices.componentType :white_check_mark: 

The indices data type.  Valid values correspond to WebGL enums: `5121` (UNSIGNED_BYTE), `5123` (UNSIGNED_SHORT), `5125` (UNSIGNED_INT).

* **Type**: `integer`
* **Required**: Yes
* **Allowed values**:
   * `5121` UNSIGNED_BYTE
   * `5123` UNSIGNED_SHORT
   * `5125` UNSIGNED_INT

### accessor.sparse.indices.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### accessor.sparse.indices.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-accessor-sparse-values"></a>
## Accessor Sparse Values

Array of size `accessor.sparse.count` times number of components storing the displaced accessor attributes pointed by `accessor.sparse.indices`.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**bufferView**|`integer`|The index of the bufferView with sparse values. Referenced bufferView can't have ARRAY_BUFFER or ELEMENT_ARRAY_BUFFER target.| :white_check_mark: Yes|
|**byteOffset**|`integer`|The offset relative to the start of the bufferView in bytes. Must be aligned.|No, default: `0`|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### accessor.sparse.values.bufferView :white_check_mark: 

The index of the bufferView with sparse values. Referenced bufferView can't have ARRAY_BUFFER or ELEMENT_ARRAY_BUFFER target.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 0`

### accessor.sparse.values.byteOffset

The offset relative to the start of the bufferView in bytes. Must be aligned.

* **Type**: `integer`
* **Required**: No, default: `0`
* **Minimum**: ` >= 0`

### accessor.sparse.values.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### accessor.sparse.values.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-animation"></a>
## Animation

A keyframe animation.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**channels**|Animation Channel `[1-*]`|An array of channels, each of which targets an animation's sampler at a node's property. Different channels of the same animation can't have equal targets.| :white_check_mark: Yes|
|**samplers**|Animation Sampler `[1-*]`|An array of samplers that combines input and output accessors with an interpolation algorithm to define a keyframe graph (but not its target).| :white_check_mark: Yes|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### animation.channels :white_check_mark: 

An array of channels, each of which targets an animation's sampler at a node's property. Different channels of the same animation can't have equal targets.

* **Type**: Animation Channel `[1-*]`
* **Required**: Yes

### animation.samplers :white_check_mark: 

An array of samplers that combines input and output accessors with an interpolation algorithm to define a keyframe graph (but not its target).

* **Type**: Animation Sampler `[1-*]`
* **Required**: Yes

### animation.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### animation.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### animation.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-animation-channel"></a>
## Animation Channel

Targets an animation's sampler at a node's property.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**sampler**|`integer`|The index of a sampler in this animation used to compute the value for the target.| :white_check_mark: Yes|
|**target**|`object`|The index of the node and TRS property to target.| :white_check_mark: Yes|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### animation.channel.sampler :white_check_mark: 

The index of a sampler in this animation used to compute the value for the target, e.g., a node's translation, rotation, or scale (TRS).

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 0`

### animation.channel.target :white_check_mark: 

The index of the node and TRS property to target.

* **Type**: `object`
* **Required**: Yes

### animation.channel.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### animation.channel.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-animation-channel-target"></a>
## Animation Channel Target

The index of the node and TRS property that an animation channel targets.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**node**|`integer`|The index of the node to target.|No|
|**path**|`string`|The name of the node's TRS property to modify, or the "weights" of the Morph Targets it instantiates. For the "translation" property, the values that are provided by the sampler are the translation along the x, y, and z axes. For the "rotation" property, the values are a quaternion in the order (x, y, z, w), where w is the scalar. For the "scale" property, the values are the scaling factors along the x, y, and z axes.| :white_check_mark: Yes|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### animation.channel.target.node

The index of the node to target.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### animation.channel.target.path :white_check_mark: 

The name of the node's TRS property to modify, or the "weights" of the Morph Targets it instantiates. For the "translation" property, the values that are provided by the sampler are the translation along the x, y, and z axes. For the "rotation" property, the values are a quaternion in the order (x, y, z, w), where w is the scalar. For the "scale" property, the values are the scaling factors along the x, y, and z axes.

* **Type**: `string`
* **Required**: Yes
* **Allowed values**:
   * `"translation"`
   * `"rotation"`
   * `"scale"`
   * `"weights"`

### animation.channel.target.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### animation.channel.target.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-animation-sampler"></a>
## Animation Sampler

Combines input and output accessors with an interpolation algorithm to define a keyframe graph (but not its target).

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**input**|`integer`|The index of an accessor containing keyframe input values, e.g., time.| :white_check_mark: Yes|
|**interpolation**|`string`|Interpolation algorithm.|No, default: `"LINEAR"`|
|**output**|`integer`|The index of an accessor, containing keyframe output values.| :white_check_mark: Yes|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### animation.sampler.input :white_check_mark: 

The index of an accessor containing keyframe input values, e.g., time. That accessor must have componentType `FLOAT`. The values represent time in seconds with `time[0] >= 0.0`, and strictly increasing values, i.e., `time[n + 1] > time[n]`.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 0`

### animation.sampler.interpolation

Interpolation algorithm.

* **Type**: `string`
* **Required**: No, default: `"LINEAR"`
* **Allowed values**:
   * `"LINEAR"` The animated values are linearly interpolated between keyframes. When targeting a rotation, spherical linear interpolation (slerp) should be used to interpolate quaternions. The number output of elements must equal the number of input elements.
   * `"STEP"` The animated values remain constant to the output of the first keyframe, until the next keyframe. The number of output elements must equal the number of input elements.
   * `"CUBICSPLINE"` The animation's interpolation is computed using a cubic spline with specified tangents. The number of output elements must equal three times the number of input elements. For each input element, the output stores three elements, an in-tangent, a spline vertex, and an out-tangent. There must be at least two keyframes when using this interpolation.

### animation.sampler.output :white_check_mark: 

The index of an accessor containing keyframe output values. When targeting translation or scale paths, the `accessor.componentType` of the output values must be `FLOAT`. When targeting rotation or morph weights, the `accessor.componentType` of the output values must be `FLOAT` or normalized integer. For weights, each output element stores `SCALAR` values with a count equal to the number of morph targets.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 0`

### animation.sampler.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### animation.sampler.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-asset"></a>
## Asset

Metadata about the glTF asset.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**copyright**|`string`|A copyright message suitable for display to credit the content creator.|No|
|**generator**|`string`|Tool that generated this glTF model.  Useful for debugging.|No|
|**version**|`string`|The glTF version that this asset targets.| :white_check_mark: Yes|
|**minVersion**|`string`|The minimum glTF version that this asset targets.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### asset.copyright

A copyright message suitable for display to credit the content creator.

* **Type**: `string`
* **Required**: No

### asset.generator

Tool that generated this glTF model.  Useful for debugging.

* **Type**: `string`
* **Required**: No

### asset.version :white_check_mark: 

The glTF version that this asset targets.

* **Type**: `string`
* **Required**: Yes

### asset.minVersion

The minimum glTF version that this asset targets.

* **Type**: `string`
* **Required**: No

### asset.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### asset.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-buffer"></a>
## Buffer

A buffer points to binary geometry, animation, or skins.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**uri**|`string`|The uri of the buffer.|No|
|**byteLength**|`integer`|The length of the buffer in bytes.| :white_check_mark: Yes|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### buffer.uri

The uri of the buffer.  Relative paths are relative to the .gltf file.  Instead of referencing an external file, the uri can also be a data-uri.

* **Type**: `string`
* **Required**: No
* **Format**: uriref

### buffer.byteLength :white_check_mark: 

The length of the buffer in bytes.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 1`

### buffer.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### buffer.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### buffer.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-buffer-view"></a>
## Buffer View

A view into a buffer generally representing a subset of the buffer.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**buffer**|`integer`|The index of the buffer.| :white_check_mark: Yes|
|**byteOffset**|`integer`|The offset into the buffer in bytes.|No, default: `0`|
|**byteLength**|`integer`|The length of the bufferView in bytes.| :white_check_mark: Yes|
|**byteStride**|`integer`|The stride, in bytes.|No|
|**target**|`integer`|The target that the GPU buffer should be bound to.|No|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### buffer.view.buffer :white_check_mark: 

The index of the buffer.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 0`

### buffer.view.byteOffset

The offset into the buffer in bytes.

* **Type**: `integer`
* **Required**: No, default: `0`
* **Minimum**: ` >= 0`

### buffer.view.byteLength :white_check_mark: 

The length of the bufferView in bytes.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 1`

### buffer.view.byteStride

The stride, in bytes, between vertex attributes.  When this is not defined, data is tightly packed. When two or more accessors use the same bufferView, this field must be defined.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 4`
* **Maximum**: ` <= 252`
* **Related WebGL functions**: `vertexAttribPointer()` stride parameter

### buffer.view.target

The target that the GPU buffer should be bound to.

* **Type**: `integer`
* **Required**: No
* **Allowed values**:
   * `34962` ARRAY_BUFFER
   * `34963` ELEMENT_ARRAY_BUFFER
* **Related WebGL functions**: `bindBuffer()`

### buffer.view.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### buffer.view.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### buffer.view.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-camera"></a>
## Camera

A camera's projection.  A node can reference a camera to apply a transform to place the camera in the scene.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**orthographic**|`object`|An orthographic camera containing properties to create an orthographic projection matrix.|No|
|**perspective**|`object`|A perspective camera containing properties to create a perspective projection matrix.|No|
|**type**|`string`|Specifies if the camera uses a perspective or orthographic projection.| :white_check_mark: Yes|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### camera.orthographic

An orthographic camera containing properties to create an orthographic projection matrix.

* **Type**: `object`
* **Required**: No

### camera.perspective

A perspective camera containing properties to create a perspective projection matrix.

* **Type**: `object`
* **Required**: No

### camera.type :white_check_mark: 

Specifies if the camera uses a perspective or orthographic projection.  Based on this, either the camera's `perspective` or `orthographic` property will be defined.

* **Type**: `string`
* **Required**: Yes
* **Allowed values**:
   * `"perspective"`
   * `"orthographic"`

### camera.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### camera.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### camera.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-camera-orthographic"></a>
## Camera Orthographic

An orthographic camera containing properties to create an orthographic projection matrix.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**xmag**|`number`|The floating-point horizontal magnification of the view. Must not be zero.| :white_check_mark: Yes|
|**ymag**|`number`|The floating-point vertical magnification of the view. Must not be zero.| :white_check_mark: Yes|
|**zfar**|`number`|The floating-point distance to the far clipping plane. `zfar` must be greater than `znear`.| :white_check_mark: Yes|
|**znear**|`number`|The floating-point distance to the near clipping plane.| :white_check_mark: Yes|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### camera.orthographic.xmag :white_check_mark: 

The floating-point horizontal magnification of the view. Must not be zero.

* **Type**: `number`
* **Required**: Yes

### camera.orthographic.ymag :white_check_mark: 

The floating-point vertical magnification of the view. Must not be zero.

* **Type**: `number`
* **Required**: Yes

### camera.orthographic.zfar :white_check_mark: 

The floating-point distance to the far clipping plane. `zfar` must be greater than `znear`.

* **Type**: `number`
* **Required**: Yes
* **Minimum**: ` > 0`

### camera.orthographic.znear :white_check_mark: 

The floating-point distance to the near clipping plane.

* **Type**: `number`
* **Required**: Yes
* **Minimum**: ` >= 0`

### camera.orthographic.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### camera.orthographic.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-camera-perspective"></a>
## Camera Perspective

A perspective camera containing properties to create a perspective projection matrix.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**aspectRatio**|`number`|The floating-point aspect ratio of the field of view.|No|
|**yfov**|`number`|The floating-point vertical field of view in radians.| :white_check_mark: Yes|
|**zfar**|`number`|The floating-point distance to the far clipping plane.|No|
|**znear**|`number`|The floating-point distance to the near clipping plane.| :white_check_mark: Yes|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### camera.perspective.aspectRatio

The floating-point aspect ratio of the field of view. When this is undefined, the aspect ratio of the canvas is used.

* **Type**: `number`
* **Required**: No
* **Minimum**: ` > 0`

### camera.perspective.yfov :white_check_mark: 

The floating-point vertical field of view in radians.

* **Type**: `number`
* **Required**: Yes
* **Minimum**: ` > 0`

### camera.perspective.zfar

The floating-point distance to the far clipping plane. When defined, `zfar` must be greater than `znear`. If `zfar` is undefined, runtime must use infinite projection matrix.

* **Type**: `number`
* **Required**: No
* **Minimum**: ` > 0`

### camera.perspective.znear :white_check_mark: 

The floating-point distance to the near clipping plane.

* **Type**: `number`
* **Required**: Yes
* **Minimum**: ` > 0`

### camera.perspective.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### camera.perspective.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-extension"></a>
## Extension

Dictionary object with extension-specific objects.

Additional properties are allowed.




---------------------------------------
<a name="reference-extras"></a>
## Extras

Application-specific data.



---------------------------------------
<a name="reference-gltf"></a>
## glTF

The root object for a glTF asset.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**extensionsUsed**|`string` `[1-*]`|Names of glTF extensions used somewhere in this asset.|No|
|**extensionsRequired**|`string` `[1-*]`|Names of glTF extensions required to properly load this asset.|No|
|**accessors**|Accessor `[1-*]`|An array of accessors.|No|
|**animations**|Animation `[1-*]`|An array of keyframe animations.|No|
|**asset**|`object`|Metadata about the glTF asset.|No|
|**buffers**|Buffer `[1-*]`|An array of buffers.|No|
|**bufferViews**|Buffer View `[1-*]`|An array of bufferViews.|No|
|**cameras**|Camera `[1-*]`|An array of cameras.|No|
|**images**|Image `[1-*]`|An array of images.|No|
|**materials**|Material `[1-*]`|An array of materials.|No|
|**meshes**|Mesh `[1-*]`|An array of meshes.|No|
|**nodes**|Node `[1-*]`|An array of nodes.|No|
|**samplers**|Sampler `[1-*]`|An array of samplers.|No|
|**scene**|`integer`|The index of the default scene.|No|
|**scenes**|Scene `[1-*]`|An array of scenes.|No|
|**skins**|Skin `[1-*]`|An array of skins.|No|
|**textures**|Texture `[1-*]`|An array of textures.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### gltf.extensionsUsed

Names of glTF extensions used somewhere in this asset.

* **Type**: `string` `[1-*]`
   * Each element in the array must be unique.
* **Required**: No

### gltf.extensionsRequired

Names of glTF extensions required to properly load this asset.

* **Type**: `string` `[1-*]`
   * Each element in the array must be unique.
* **Required**: No

### gltf.accessors

An array of accessors.  An accessor is a typed view into a bufferView.

* **Type**: Accessor `[1-*]`
* **Required**: No

### gltf.animations

An array of keyframe animations.

* **Type**: Animation `[1-*]`
* **Required**: No

### gltf.asset

Metadata about the glTF asset.

* **Type**: `object`
* **Required**: No

### gltf.buffers

An array of buffers.  A buffer points to binary geometry, animation, or skins.

* **Type**: Buffer `[1-*]`
* **Required**: No

### gltf.bufferViews

An array of bufferViews.  A bufferView is a view into a buffer generally representing a subset of the buffer.

* **Type**: Buffer View `[1-*]`
* **Required**: No

### gltf.cameras

An array of cameras.  A camera defines a projection matrix.

* **Type**: Camera `[1-*]`
* **Required**: No

### gltf.images

An array of images.  An image defines data used to create a texture.

* **Type**: Image `[1-*]`
* **Required**: No

### gltf.materials

An array of materials.  A material defines the appearance of a primitive.

* **Type**: Material `[1-*]`
* **Required**: No

### gltf.meshes

An array of meshes.  A mesh is a set of primitives to be rendered.

* **Type**: Mesh `[1-*]`
* **Required**: No

### gltf.nodes

An array of nodes.

* **Type**: Node `[1-*]`
* **Required**: No

### gltf.samplers

An array of samplers.  A sampler contains properties for texture filtering and wrapping modes.

* **Type**: Sampler `[1-*]`
* **Required**: No

### gltf.scene

The index of the default scene.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### gltf.scenes

An array of scenes.

* **Type**: Scene `[1-*]`
* **Required**: No

### gltf.skins

An array of skins.  A skin is defined by joints and matrices.

* **Type**: Skin `[1-*]`
* **Required**: No

### gltf.textures

An array of textures.

* **Type**: Texture `[1-*]`
* **Required**: No

### gltf.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### gltf.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-gltf-child-of-root-property"></a>
## glTF Child of Root Property

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### gltf.child.of.root.property.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### gltf.child.of.root.property.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### gltf.child.of.root.property.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-gltf-id"></a>
## glTF Id



---------------------------------------
<a name="reference-gltf-property"></a>
## glTF Property

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### gltf.property.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### gltf.property.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-image"></a>
## Image

Image data used to create a texture. Image can be referenced by URI or `bufferView` index. `mimeType` is required in the latter case.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**uri**|`string`|The uri of the image.|No|
|**mimeType**|`string`|The image's MIME type. Required if `bufferView` is defined.|No|
|**bufferView**|`integer`|The index of the bufferView that contains the image. Use this instead of the image's uri property.|No|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### image.uri

The uri of the image.  Relative paths are relative to the .gltf file.  Instead of referencing an external file, the uri can also be a data-uri.  The image format must be jpg or png.

* **Type**: `string`
* **Required**: No
* **Format**: uriref

### image.mimeType

The image's MIME type. Required if `bufferView` is defined.

* **Type**: `string`
* **Required**: No
* **Allowed values**:
   * `"image/jpeg"`
   * `"image/png"`

### image.bufferView

The index of the bufferView that contains the image. Use this instead of the image's uri property.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### image.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### image.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### image.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-material"></a>
## Material

The material appearance of a primitive.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|
|**pbrMetallicRoughness**|`object`|A set of parameter values that are used to define the metallic-roughness material model from Physically-Based Rendering (PBR) methodology. When not specified, all the default values of `pbrMetallicRoughness` apply.|No|
|**normalTexture**|`object`|The normal map texture.|No|
|**occlusionTexture**|`object`|The occlusion map texture.|No|
|**emissiveTexture**|`object`|The emissive map texture.|No|
|**emissiveFactor**|`number` `[3]`|The emissive color of the material.|No, default: `[0,0,0]`|
|**alphaMode**|`string`|The alpha rendering mode of the material.|No, default: `"OPAQUE"`|
|**alphaCutoff**|`number`|The alpha cutoff value of the material.|No, default: `0.5`|
|**doubleSided**|`boolean`|Specifies whether the material is double sided.|No, default: `false`|

Additional properties are allowed.

### material.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### material.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### material.extras

Application-specific data.

* **Type**: `any`
* **Required**: No

### material.pbrMetallicRoughness

A set of parameter values that are used to define the metallic-roughness material model from Physically-Based Rendering (PBR) methodology. When not specified, all the default values of `pbrMetallicRoughness` apply.

* **Type**: `object`
* **Required**: No

### material.normalTexture

A tangent space normal map. The texture contains RGB components in linear space. Each texel represents the XYZ components of a normal vector in tangent space. Red [0 to 255] maps to X [-1 to 1]. Green [0 to 255] maps to Y [-1 to 1]. Blue [128 to 255] maps to Z [1/255 to 1]. The normal vectors use OpenGL conventions where +X is right and +Y is up. +Z points toward the viewer. In GLSL, this vector would be unpacked like so: `float3 normalVector = tex2D(<sampled normal map texture value>, texCoord) * 2 - 1`. Client implementations should normalize the normal vectors before using them in lighting equations.

* **Type**: `object`
* **Required**: No

### material.occlusionTexture

The occlusion map texture. The occlusion values are sampled from the R channel. Higher values indicate areas that should receive full indirect lighting and lower values indicate no indirect lighting. These values are linear. If other channels are present (GBA), they are ignored for occlusion calculations.

* **Type**: `object`
* **Required**: No

### material.emissiveTexture

The emissive map controls the color and intensity of the light being emitted by the material. This texture contains RGB components in sRGB color space. If a fourth component (A) is present, it is ignored.

* **Type**: `object`
* **Required**: No

### material.emissiveFactor

The RGB components of the emissive color of the material. These values are linear. If an emissiveTexture is specified, this value is multiplied with the texel values.

* **Type**: `number` `[3]`
   * Each element in the array must be greater than or equal to `0` and less than or equal to `1`.
* **Required**: No, default: `[0,0,0]`

### material.alphaMode

The material's alpha rendering mode enumeration specifying the interpretation of the alpha value of the main factor and texture.

* **Type**: `string`
* **Required**: No, default: `"OPAQUE"`
* **Allowed values**:
   * `"OPAQUE"` The alpha value is ignored and the rendered output is fully opaque.
   * `"MASK"` The rendered output is either fully opaque or fully transparent depending on the alpha value and the specified alpha cutoff value.
   * `"BLEND"` The alpha value is used to composite the source and destination areas. The rendered output is combined with the background using the normal painting operation (i.e. the Porter and Duff over operator).

### material.alphaCutoff

Specifies the cutoff threshold when in `MASK` mode. If the alpha value is greater than or equal to this value then it is rendered as fully opaque, otherwise, it is rendered as fully transparent. A value greater than 1.0 will render the entire material as fully transparent. This value is ignored for other modes.

* **Type**: `number`
* **Required**: No, default: `0.5`
* **Minimum**: ` >= 0`

### material.doubleSided

Specifies whether the material is double sided. When this value is false, back-face culling is enabled. When this value is true, back-face culling is disabled and double sided lighting is enabled. The back-face must have its normals reversed before the lighting equation is evaluated.

* **Type**: `boolean`
* **Required**: No, default: `false`




---------------------------------------
<a name="reference-material-normal-texture-info"></a>
## Material Normal Texture Info

Reference to a texture.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**index**|`integer`|The index of the texture.| :white_check_mark: Yes|
|**texCoord**|`integer`|The set index of texture's TEXCOORD attribute used for texture coordinate mapping.|No, default: `0`|
|**scale**|`number`|The scalar multiplier applied to each normal vector of the normal texture.|No, default: `1`|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### material.normal.texture.info.index :white_check_mark: 

The index of the texture.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 0`

### material.normal.texture.info.texCoord

This integer value is used to construct a string in the format `TEXCOORD_<set index>` which is a reference to a key in mesh.primitives.attributes (e.g. A value of `0` corresponds to `TEXCOORD_0`). Mesh must have corresponding texture coordinate attributes for the material to be applicable to it.

* **Type**: `integer`
* **Required**: No, default: `0`
* **Minimum**: ` >= 0`

### material.normal.texture.info.scale

The scalar multiplier applied to each normal vector of the texture. This value scales the normal vector using the formula: `scaledNormal =  normalize((<sampled normal texture value> * 2.0 - 1.0) * vec3(<normal scale>, <normal scale>, 1.0))`. This value is ignored if normalTexture is not specified. This value is linear.

* **Type**: `number`
* **Required**: No, default: `1`

### material.normal.texture.info.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### material.normal.texture.info.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-material-occlusion-texture-info"></a>
## Material Occlusion Texture Info

Reference to a texture.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**index**|`integer`|The index of the texture.| :white_check_mark: Yes|
|**texCoord**|`integer`|The set index of texture's TEXCOORD attribute used for texture coordinate mapping.|No, default: `0`|
|**strength**|`number`|A scalar multiplier controlling the amount of occlusion applied.|No, default: `1`|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### material.occlusion.texture.info.index :white_check_mark: 

The index of the texture.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 0`

### material.occlusion.texture.info.texCoord

This integer value is used to construct a string in the format `TEXCOORD_<set index>` which is a reference to a key in mesh.primitives.attributes (e.g. A value of `0` corresponds to `TEXCOORD_0`). Mesh must have corresponding texture coordinate attributes for the material to be applicable to it.

* **Type**: `integer`
* **Required**: No, default: `0`
* **Minimum**: ` >= 0`

### material.occlusion.texture.info.strength

A scalar multiplier controlling the amount of occlusion applied. A value of 0.0 means no occlusion. A value of 1.0 means full occlusion. This value affects the resulting color using the formula: `occludedColor = lerp(color, color * <sampled occlusion texture value>, <occlusion strength>)`. This value is ignored if the corresponding texture is not specified. This value is linear.

* **Type**: `number`
* **Required**: No, default: `1`
* **Minimum**: ` >= 0`
* **Maximum**: ` <= 1`

### material.occlusion.texture.info.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### material.occlusion.texture.info.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-material-pbr-metallic-roughness"></a>
## Material PBR Metallic Roughness

A set of parameter values that are used to define the metallic-roughness material model from Physically-Based Rendering (PBR) methodology.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**baseColorFactor**|`number` `[4]`|The material's base color factor.|No, default: `[1,1,1,1]`|
|**baseColorTexture**|`object`|The base color texture.|No|
|**metallicFactor**|`number`|The metalness of the material.|No, default: `1`|
|**roughnessFactor**|`number`|The roughness of the material.|No, default: `1`|
|**metallicRoughnessTexture**|`object`|The metallic-roughness texture.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### material.pbr.metallic.roughness.baseColorFactor

The RGBA components of the base color of the material. The fourth component (A) is the alpha coverage of the material. The `alphaMode` property specifies how alpha is interpreted. These values are linear. If a baseColorTexture is specified, this value is multiplied with the texel values.

* **Type**: `number` `[4]`
   * Each element in the array must be greater than or equal to `0` and less than or equal to `1`.
* **Required**: No, default: `[1,1,1,1]`

### material.pbr.metallic.roughness.baseColorTexture

The base color texture. This texture contains RGB(A) components in sRGB color space. The first three components (RGB) specify the base color of the material. If the fourth component (A) is present, it represents the alpha coverage of the material. Otherwise, an alpha of 1.0 is assumed. The `alphaMode` property specifies how alpha is interpreted. The stored texels must not be premultiplied.

* **Type**: `object`
* **Required**: No

### material.pbr.metallic.roughness.metallicFactor

The metalness of the material. A value of 1.0 means the material is a metal. A value of 0.0 means the material is a dielectric. Values in between are for blending between metals and dielectrics such as dirty metallic surfaces. This value is linear. If a metallicRoughnessTexture is specified, this value is multiplied with the metallic texel values.

* **Type**: `number`
* **Required**: No, default: `1`
* **Minimum**: ` >= 0`
* **Maximum**: ` <= 1`

### material.pbr.metallic.roughness.roughnessFactor

The roughness of the material. A value of 1.0 means the material is completely rough. A value of 0.0 means the material is completely smooth. This value is linear. If a metallicRoughnessTexture is specified, this value is multiplied with the roughness texel values.

* **Type**: `number`
* **Required**: No, default: `1`
* **Minimum**: ` >= 0`
* **Maximum**: ` <= 1`

### material.pbr.metallic.roughness.metallicRoughnessTexture

The metallic-roughness texture. The metalness values are sampled from the B channel. The roughness values are sampled from the G channel. These values are linear. If other channels are present (R or A), they are ignored for metallic-roughness calculations.

* **Type**: `object`
* **Required**: No

### material.pbr.metallic.roughness.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### material.pbr.metallic.roughness.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-mesh"></a>
## Mesh

A set of primitives to be rendered.  A node can contain one mesh.  A node's transform places the mesh in the scene.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**primitives**|Mesh Primitive `[1-*]`|An array of primitives, each defining geometry to be rendered with a material.| :white_check_mark: Yes|
|**weights**|`number` `[1-*]`|Array of weights to be applied to the Morph Targets.|No|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### mesh.primitives :white_check_mark: 

An array of primitives, each defining geometry to be rendered with a material.

* **Type**: Mesh Primitive `[1-*]`
* **Required**: Yes

### mesh.weights

Array of weights to be applied to the Morph Targets.

* **Type**: `number` `[1-*]`
* **Required**: No

### mesh.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### mesh.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### mesh.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-mesh-primitive"></a>
## Mesh Primitive

Geometry to be rendered with the given material.

**Related WebGL functions**: `drawElements()` and `drawArrays()`

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**attributes**|`object`|A dictionary object, where each key corresponds to mesh attribute semantic and each value is the index of the accessor containing attribute's data.| :white_check_mark: Yes|
|**indices**|`integer`|The index of the accessor that contains the indices.|No|
|**material**|`integer`|The index of the material to apply to this primitive when rendering.|No|
|**mode**|`integer`|The type of primitives to render.|No, default: `4`|
|**targets**|`object` `[1-*]`|An array of Morph Targets, each  Morph Target is a dictionary mapping attributes (only `POSITION`, `NORMAL`, and `TANGENT` supported) to their deviations in the Morph Target.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### mesh.primitive.attributes :white_check_mark: 

A dictionary object, where each key corresponds to mesh attribute semantic and each value is the index of the accessor containing attribute's data.

* **Type**: `object`
* **Required**: Yes
* **Type of each property**: `integer`

### mesh.primitive.indices

The index of the accessor that contains mesh indices.  When this is not defined, the primitives should be rendered without indices using `drawArrays()`.  When defined, the accessor must contain indices: the `bufferView` referenced by the accessor should have a `target` equal to 34963 (ELEMENT_ARRAY_BUFFER); `componentType` must be 5121 (UNSIGNED_BYTE), 5123 (UNSIGNED_SHORT) or 5125 (UNSIGNED_INT), the latter may require enabling additional hardware support; `type` must be `"SCALAR"`. For triangle primitives, the front face has a counter-clockwise (CCW) winding order.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### mesh.primitive.material

The index of the material to apply to this primitive when rendering.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### mesh.primitive.mode

The type of primitives to render. All valid values correspond to WebGL enums.

* **Type**: `integer`
* **Required**: No, default: `4`
* **Allowed values**:
   * `0` POINTS
   * `1` LINES
   * `2` LINE_LOOP
   * `3` LINE_STRIP
   * `4` TRIANGLES
   * `5` TRIANGLE_STRIP
   * `6` TRIANGLE_FAN

### mesh.primitive.targets

An array of Morph Targets, each  Morph Target is a dictionary mapping attributes (only `POSITION`, `NORMAL`, and `TANGENT` supported) to their deviations in the Morph Target.

* **Type**: `object` `[1-*]`
* **Required**: No

### mesh.primitive.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### mesh.primitive.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-node"></a>
## Node

A node in the node hierarchy.  When the node contains `skin`, all `mesh.primitives` must contain `JOINTS_0` and `WEIGHTS_0` attributes.  A node can have either a `matrix` or any combination of `translation`/`rotation`/`scale` (TRS) properties. TRS properties are converted to matrices and postmultiplied in the `T * R * S` order to compose the transformation matrix; first the scale is applied to the vertices, then the rotation, and then the translation. If none are provided, the transform is the identity. When a node is targeted for animation (referenced by an animation.channel.target), only TRS properties may be present; `matrix` will not be present.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**camera**|`integer`|The index of the camera referenced by this node.|No|
|**children**|`integer` `[1-*]`|The indices of this node's children.|No|
|**skin**|`integer`|The index of the skin referenced by this node.|No|
|**matrix**|`number` `[16]`|A floating-point 4x4 transformation matrix stored in column-major order.|No, default: `[1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1]`|
|**mesh**|`integer`|The index of the mesh in this node.|No|
|**rotation**|`number` `[4]`|The node's unit quaternion rotation in the order (x, y, z, w), where w is the scalar.|No, default: `[0,0,0,1]`|
|**scale**|`number` `[3]`|The node's non-uniform scale, given as the scaling factors along the x, y, and z axes.|No, default: `[1,1,1]`|
|**translation**|`number` `[3]`|The node's translation along the x, y, and z axes.|No, default: `[0,0,0]`|
|**weights**|`number` `[1-*]`|The weights of the instantiated Morph Target. Number of elements must match number of Morph Targets of used mesh.|No|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### node.camera

The index of the camera referenced by this node.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### node.children

The indices of this node's children.

* **Type**: `integer` `[1-*]`
   * Each element in the array must be unique.
   * Each element in the array must be greater than or equal to `0`.
* **Required**: No

### node.skin

The index of the skin referenced by this node.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### node.matrix

A floating-point 4x4 transformation matrix stored in column-major order.

* **Type**: `number` `[16]`
* **Required**: No, default: `[1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1]`
* **Related WebGL functions**: `uniformMatrix4fv()` with the transpose parameter equal to false

### node.mesh

The index of the mesh in this node.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### node.rotation

The node's unit quaternion rotation in the order (x, y, z, w), where w is the scalar.

* **Type**: `number` `[4]`
   * Each element in the array must be greater than or equal to `-1` and less than or equal to `1`.
* **Required**: No, default: `[0,0,0,1]`

### node.scale

The node's non-uniform scale, given as the scaling factors along the x, y, and z axes.

* **Type**: `number` `[3]`
* **Required**: No, default: `[1,1,1]`

### node.translation

The node's translation along the x, y, and z axes.

* **Type**: `number` `[3]`
* **Required**: No, default: `[0,0,0]`

### node.weights

The weights of the instantiated Morph Target. Number of elements must match number of Morph Targets of used mesh.

* **Type**: `number` `[1-*]`
* **Required**: No

### node.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### node.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### node.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-sampler"></a>
## Sampler

Texture sampler properties for filtering and wrapping modes.

**Related WebGL functions**: `texParameterf()`

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**magFilter**|`integer`|Magnification filter.|No|
|**minFilter**|`integer`|Minification filter.|No|
|**wrapS**|`integer`|s wrapping mode.|No, default: `10497`|
|**wrapT**|`integer`|t wrapping mode.|No, default: `10497`|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### sampler.magFilter

Magnification filter.  Valid values correspond to WebGL enums: `9728` (NEAREST) and `9729` (LINEAR).

* **Type**: `integer`
* **Required**: No
* **Allowed values**:
   * `9728` NEAREST
   * `9729` LINEAR
* **Related WebGL functions**: `texParameterf()` with pname equal to TEXTURE_MAG_FILTER

### sampler.minFilter

Minification filter.  All valid values correspond to WebGL enums.

* **Type**: `integer`
* **Required**: No
* **Allowed values**:
   * `9728` NEAREST
   * `9729` LINEAR
   * `9984` NEAREST_MIPMAP_NEAREST
   * `9985` LINEAR_MIPMAP_NEAREST
   * `9986` NEAREST_MIPMAP_LINEAR
   * `9987` LINEAR_MIPMAP_LINEAR
* **Related WebGL functions**: `texParameterf()` with pname equal to TEXTURE_MIN_FILTER

### sampler.wrapS

S (U) wrapping mode.  All valid values correspond to WebGL enums.

* **Type**: `integer`
* **Required**: No, default: `10497`
* **Allowed values**:
   * `33071` CLAMP_TO_EDGE
   * `33648` MIRRORED_REPEAT
   * `10497` REPEAT
* **Related WebGL functions**: `texParameterf()` with pname equal to TEXTURE_WRAP_S

### sampler.wrapT

T (V) wrapping mode.  All valid values correspond to WebGL enums.

* **Type**: `integer`
* **Required**: No, default: `10497`
* **Allowed values**:
   * `33071` CLAMP_TO_EDGE
   * `33648` MIRRORED_REPEAT
   * `10497` REPEAT
* **Related WebGL functions**: `texParameterf()` with pname equal to TEXTURE_WRAP_T

### sampler.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### sampler.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### sampler.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-scene"></a>
## Scene

The root nodes of a scene.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**nodes**|`integer` `[1-*]`|The indices of each root node.|No|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### scene.nodes

The indices of each root node.

* **Type**: `integer` `[1-*]`
   * Each element in the array must be unique.
   * Each element in the array must be greater than or equal to `0`.
* **Required**: No

### scene.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### scene.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### scene.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-skin"></a>
## Skin

Joints and matrices defining a skin.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**inverseBindMatrices**|`integer`|The index of the accessor containing the floating-point 4x4 inverse-bind matrices.  The default is that each matrix is a 4x4 identity matrix, which implies that inverse-bind matrices were pre-applied.|No|
|**skeleton**|`integer`|The index of the node used as a skeleton root. When undefined, joints transforms resolve to scene root.|No|
|**joints**|`integer` `[1-*]`|Indices of skeleton nodes, used as joints in this skin.| :white_check_mark: Yes|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### skin.inverseBindMatrices

The index of the accessor containing the floating-point 4x4 inverse-bind matrices.  The default is that each matrix is a 4x4 identity matrix, which implies that inverse-bind matrices were pre-applied.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### skin.skeleton

The index of the node used as a skeleton root. When undefined, joints transforms resolve to scene root.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### skin.joints :white_check_mark: 

Indices of skeleton nodes, used as joints in this skin.  The array length must be the same as the `count` property of the `inverseBindMatrices` accessor (when defined).

* **Type**: `integer` `[1-*]`
   * Each element in the array must be unique.
   * Each element in the array must be greater than or equal to `0`.
* **Required**: Yes

### skin.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### skin.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### skin.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-texture"></a>
## Texture

A texture and its sampler.

**Related WebGL functions**: `createTexture()`, `deleteTexture()`, `bindTexture()`, `texImage2D()`, and `texParameterf()`

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**sampler**|`integer`|The index of the sampler used by this texture. When undefined, a sampler with repeat wrapping and auto filtering should be used.|No|
|**source**|`integer`|The index of the image used by this texture.|No|
|**name**|`string`|The user-defined name of this object.|No|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### texture.sampler

The index of the sampler used by this texture. When undefined, a sampler with repeat wrapping and auto filtering should be used.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### texture.source

The index of the image used by this texture.

* **Type**: `integer`
* **Required**: No
* **Minimum**: ` >= 0`

### texture.name

The user-defined name of this object.  This is not necessarily unique, e.g., an accessor and a buffer could have the same name, or two accessors could even have the same name.

* **Type**: `string`
* **Required**: No

### texture.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### texture.extras

Application-specific data.

* **Type**: `any`
* **Required**: No




---------------------------------------
<a name="reference-texture-info"></a>
## Texture Info

Reference to a texture.

**Properties**

|   |Type|Description|Required|
|---|----|-----------|--------|
|**index**|`integer`|The index of the texture.| :white_check_mark: Yes|
|**texCoord**|`integer`|The set index of texture's TEXCOORD attribute used for texture coordinate mapping.|No, default: `0`|
|**extensions**|`object`|Dictionary object with extension-specific objects.|No|
|**extras**|`any`|Application-specific data.|No|

Additional properties are allowed.

### texture.info.index :white_check_mark: 

The index of the texture.

* **Type**: `integer`
* **Required**: Yes
* **Minimum**: ` >= 0`

### texture.info.texCoord

This integer value is used to construct a string in the format `TEXCOORD_<set index>` which is a reference to a key in mesh.primitives.attributes (e.g. A value of `0` corresponds to `TEXCOORD_0`). Mesh must have corresponding texture coordinate attributes for the material to be applicable to it.

* **Type**: `integer`
* **Required**: No, default: `0`
* **Minimum**: ` >= 0`

### texture.info.extensions

Dictionary object with extension-specific objects.

* **Type**: `object`
* **Required**: No
* **Type of each property**: Extension

### texture.info.extras

Application-specific data.

* **Type**: `any`
* **Required**: No


